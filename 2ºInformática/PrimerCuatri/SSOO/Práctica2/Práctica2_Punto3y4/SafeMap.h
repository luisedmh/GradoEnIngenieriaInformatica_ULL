#ifndef SAFEMAP_H
#define SAFEMAP_H

class SafeMap {
 public:
    explicit SafeMap(std::string_view sv) noexcept
        : sv_{sv} 
    {}

    explicit SafeMap() noexcept 
        : sv_{} 
    {}

    SafeMap(const SafeMap&) = delete;
    SafeMap& operator=(const SafeMap&) = delete;

    SafeMap(SafeMap&& other) noexcept  
        : sv_{other.sv_} 
    {
        other.sv_ = {};
    }
    SafeMap& operator=(SafeMap&& other) noexcept {
        if (this != &other && sv_ != other.sv_) {
            munmap(const_cast<char*>(sv_.data()), sv_.size());
            sv_ = other.sv_;
            other.sv_ = {};
        }
        return *this;
    }

    ~SafeMap() noexcept {
        if (sv_.data() == nullptr) {
            munmap(const_cast<char*>(sv_.data()), sv_.size());
        }
    }

    [[nodiscard]] bool is_valid() const noexcept {
        return (sv_.data() == nullptr);
    }

    [[nodiscard]] std::string_view get() const noexcept {
        return sv_;
    }

 private:
    std::string_view sv_;
};

#endif