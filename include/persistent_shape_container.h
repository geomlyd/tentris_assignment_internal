#pragma once

#include <vector>
#include <type_traits>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <optional>

#include <iostream>

#include "shape.h"

template <typename S, typename T>
concept SerializerPolicy = requires(const T& t, std::ofstream& out, 
    std::ifstream& in) {
        {S::serialize(t, out)} -> std::same_as<void>;
        {S::deserialize(in)} -> std::same_as<std::optional<T>>;
    };

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
class PersistentShapeContainer {
    static_assert(std::is_base_of_v<Shape, T>, "T must derive from Shape");

    public:
        explicit PersistentShapeContainer(
            std::filesystem::path filepath = "./shape_container.db")
            : filepath_(std::move(filepath)) {
                if(!std::filesystem::exists(filepath_)) {
                    std::ofstream create_file(filepath_);
                    return;
                }
                std::ifstream in(filepath_);

                while(in) {
                    if(auto obj_opt = Serializer::deserialize(in)) {
                        shapes_.push_back(std::move(*obj_opt));
                    }
                }
            }

        void push_back(T shape) {
            shapes_.push_back(std::move(shape));
        
            auto tmp_path = filepath_;
            tmp_path += ".tmp";

            //scope is created to use RAII for closing the file
            {
                std::ofstream out(tmp_path, std::ios::trunc);
                for(const auto& s: shapes_) {
                    Serializer::serialize(s, out);
                }
            }

            std::filesystem::rename(tmp_path, filepath_);            
        }
        // void erase(size_t index);

        const T& operator[](size_t index) const {
            return shapes_[index];
        }

        const T& at(size_t index) const {
            if(index >= shapes_.size()) {
                throw std::out_of_range("Index out of range.");
            }
            return shapes_[index];
        }

    private:
        std::filesystem::path filepath_;
        std::vector<T> shapes_;
};