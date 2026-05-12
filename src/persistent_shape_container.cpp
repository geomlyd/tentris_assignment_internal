#include "persistent_shape_container.h"

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
PersistentShapeContainer<T, Serializer>::PersistentShapeContainer(
    std::filesystem::path filepath) : filepath_(std::move(filepath)) {
    if(!std::filesystem::exists(filepath)) {
        std::ofstream create_file(filepath_);
        return;
    }
    std::ifstream in(filepath_);

    while(in.good()) {
        shapes_.push_back(Serializer::deserialize(in));
    }
}

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
void PersistentShapeContainer<T, Serializer>::push_back(T shape) {
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

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
const T& PersistentShapeContainer<T, Serializer>::operator[](
    size_t index) const {
    return shapes_[index];
}

template <typename T, typename Serializer>
    requires SerializerPolicy<Serializer, T>
const T& PersistentShapeContainer<T, Serializer>::at(size_t index) const {
    if(index >= shapes_.size()) {
        throw std::out_of_range("Index out of range.");
    }
    return shapes_[index];
}
