#ifndef SAFEFD_H
#define SAFEFD_H

class SafeFD {
 public:
    SafeFD() noexcept
        : fd_ {-1}
    {}
    SafeFD(int fd) noexcept
        : fd_ {fd}
    {}

    SafeFD(const SafeFD&) = delete;
    SafeFD& operator=(const SafeFD&) = delete;
    
    SafeFD(SafeFD&& other) noexcept
        : fd_ {other.fd_}
    {
        other.fd_ = -1;
    }

    SafeFD& operator=(SafeFD&& other) noexcept {
        if (this != &other && fd_ != other.fd_) {
            close(fd_);
            fd_ = other.fd_;
            other.fd_ = -1;
        }
        return *this;
    }
    
    ~SafeFD() noexcept {
        if (fd_ >= 0) {
            close(fd_);
        }
    }
    [[nodiscard]] bool is_valid() const noexcept {
        return fd_ >= 0;
    }
    [[nodiscard]] int get() const noexcept {
        return fd_;
    }
 private:
    int fd_;
};

#endif