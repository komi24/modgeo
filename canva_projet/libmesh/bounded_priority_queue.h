#include <queue>
#include <stdexcept>
#include <algorithm>

template <class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>
         > class bounded_priority_queue {
    public:
        typedef T value_type;
        typedef std::size_t size_type;

        explicit bounded_priority_queue (const size_type& maxsize)
         : maxsize_(maxsize)
        {
            if (maxsize_ < 1)
                throw std::runtime_error("bpqueue maxsize<1");
        }

        void push (const value_type& val) {
            queue_.push(val);
            if (queue_.size() > maxsize_)
                queue_.pop();
        }

        T pop() {
            bounded_priority_queue tmp(*this);
            T result = tmp.queue_.top();
            tmp.queue_.pop();
            return result;
        }

        std::priority_queue<T> pop_all () {
            std::priority_queue<T> result;

            bounded_priority_queue tmp(*this);
            while (!tmp.queue_.empty()) {
                result.push(tmp.queue_.top());
                tmp.queue_.pop();
            }

            std::swap(this->queue_, tmp.queue_); // specialized ptr swap
            return result; // return value optimization
        }

    private:
        struct reversed_compare : Compare {
            // notice that all four versions are required
            // so that no new restrictions are created:
            // (you might even want mixed const params..)

            bool operator() (const T& l, const T &r) {
                return Compare::operator()(r, l);
            }

            bool operator() (const T& l, const T& r) const {
                return Compare::operator()(r, l);
            }

            bool operator() (T& l, T& r) {
                return Compare::operator()(r, l);
            }

            bool operator() (T& l, T& r) const {
                return Compare::operator()(r, l);
            }
        };

        std::priority_queue<T, Container, reversed_compare> queue_;
        size_type maxsize_; // not const to stay assignable
};
