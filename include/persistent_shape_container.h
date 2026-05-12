#pragma once

#include <vector>
#include <type_traits>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include <filesystem>

#include "shape.h"

template <typename S, typename T>
concept SerializerPolicy = requires(T t, std::ofstream& out, 
    std::ifstream& in) {
        S::serialize(t, out);
        {S::deserialize(in)} -> std::same_as<T>;
    };

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
class PersistentShapeContainer {
    static_assert(std::is_base_of_v<Shape, T>, "T must derive from Shape");

    public:
        explicit PersistentShapeContainer(
            std::filesystem::path filepath = "./shape_container.db");

        void push_back(T shape);
        void erase(size_t index);

        const T& operator[](size_t index) const;
        const T& at(size_t index) const;

    private:
        std::filesystem::path filepath_;
        std::vector<T> shapes_;
};