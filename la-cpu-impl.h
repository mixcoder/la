namespace la {

    namespace cpu {

        // vector

        template <class T>
        vector<T>::vector()
        {}

        template <class T>
        vector<T>::vector(std::vector<T> const& data)
            : data_(data)
        {}

        template <class T>
        vector<T>::vector(std::vector<T>&& data)
            : data_(std::move(data))
        {}

        template <class T>
        vector<T>::vector(vector_like<T> const& v)
            : data_(v.data(), v.data() + v.size())
        {}

        template <class T>
        vector<T>::vector(std::initializer_list<T> list)
            : data_(list)
        {}

        template <class T>
        T* vector<T>::data()
        {
            return data_.data();
        }

        template <class T>
        T const* vector<T>::data() const
        {
            return data_.data();
        }

        template <class T>
        unsigned int vector<T>::size() const
        {
            return data_.size();
        }

        template <class T>
        T& vector<T>::operator()(int i)
        {
            return data_[i];
        }

        template <class T>
        T const& vector<T>::operator()(int i) const
        {
            return data_[i];
        }

        template <class T>
        T& vector<T>::at(int i)
        {
            return data_.at(i);
        }

        template <class T>
        T const& vector<T>::at(int i) const
        {
            return data_.at(i);
        }

        template <class T>
        void vector<T>::resize(unsigned int size, T value)
        {
            data_.resize(size, value);
        }

        // weak_vector

        template <class T>
        weak_vector<T>::weak_vector(vector_like<T>& data)
            : data_(data.data()), size_(data.size())
        {}

        template <class T>
        weak_vector<T>::weak_vector(T *data, unsigned int size)
            : data_(data), size_(size)
        {}

        template <class T>
        T* weak_vector<T>::data()
        {
            return data_;
        }

        template <class T>
        T const* weak_vector<T>::data() const
        {
            return data_;
        }

        template <class T>
        unsigned int weak_vector<T>::size() const
        {
            return size_;
        }

        template <class T>
        T& weak_vector<T>::operator()(int i)
        {
            return data_[i];
        }

        template <class T>
        T const& weak_vector<T>::operator()(int i) const
        {
            return data_[i];
        }

        template <class T>
        T& weak_vector<T>::at(int i)
        {
            assert(i < size_);
            return data_[i];
        }

        template <class T>
        T const& weak_vector<T>::at(int i) const
        {
            assert(i < size_);
            return data_[i];
        }

        // matrix

        template <class T>
        matrix<T>::matrix()
        {}

        template <class T>
        matrix<T>::matrix(std::vector<std::vector<T>> data)
        {
            std::vector<T> m;

            rows_ = data.size();
            cols_ = data.front().size();

            for (auto& v: data) {
                m.insert(m.end(), v.begin(), v.end());
            }

            data_ = vector<T>(std::move(m));
        }

        template <class T>
        matrix<T>::matrix(matrix_like<T> const& m)
            : data_(std::vector<T> { m.data(), m.data() + m.rows() * m.cols() })
            , rows_(m.rows()), cols_(m.cols())
        {}

        template <class T>
        matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> data)
        {
            std::vector<T> m;

            rows_ = data.size();
            cols_ = data.begin()->size();

            for (auto& v: data) {
                m.insert(m.end(), v.begin(), v.end());
            }

            data_ = vector<T>(std::move(m));
        }

        template <class T>
        T* matrix<T>::data()
        {
            return data_.data();
        }

        template <class T>
        T const* matrix<T>::data() const
        {
            return data_.data();
        }

        template <class T>
        unsigned int matrix<T>::rows() const
        {
            return rows_;
        }

        template <class T>
        unsigned int matrix<T>::cols() const
        {
            return cols_;
        }

        template <class T>
        T& matrix<T>::operator()(unsigned int r, unsigned int c)
        {
            return data_(r * cols_ + c);
        }

        template <class T>
        T const& matrix<T>::operator()(unsigned int r, unsigned int c) const
        {
            return data_(r * cols_ + c);
        }

        template <class T>
        T& matrix<T>::at(unsigned int r, unsigned int c)
        {
            return data_.at(r * cols_ + c);
        }

        template <class T>
        T const& matrix<T>::at(unsigned int r, unsigned int c) const
        {
            return data_.at(r * cols_ + c);
        }

        template <class T>
        void matrix<T>::resize(unsigned int rows, unsigned int cols, T value)
        {
            data_.resize(rows * cols, value);
            rows_ = rows;
            cols_ = cols;
        }

        template <class T>
        vector_like<T>& matrix<T>::as_vector()
        {
            return data_;
        }

        template <class T>
        vector_like<T> const& matrix<T>::as_vector() const
        {
            return data_;
        }

        // weak_matrix

        template <class T>
        weak_matrix<T>::weak_matrix(matrix_like<T>& data)
            : data_(data.data(), data.rows() * data.cols()), rows_(data.rows()), cols_(data.cols())
        {} 

        template <class T>
        weak_matrix<T>::weak_matrix(T *data, unsigned int rows, unsigned int cols)
            : data_(data, rows * cols), rows_(rows), cols_(cols)
        {} 

        template <class T>
        T* weak_matrix<T>::data()
        {
            return data_.data();
        }

        template <class T>
        T const* weak_matrix<T>::data() const
        {
            return data_.data();
        }

        template <class T>
        unsigned int weak_matrix<T>::rows() const
        {
            return rows_;
        }

        template <class T>
        unsigned int weak_matrix<T>::cols() const
        {
            return cols_;
        }

        template <class T>
        T& weak_matrix<T>::operator()(unsigned int r, unsigned int c)
        {
            return data_(r * cols_ + c);
        }

        template <class T>
        T const& weak_matrix<T>::operator()(unsigned int r, unsigned int c) const
        {
            return data_(r * cols_ + c);
        }

        template <class T>
        T& weak_matrix<T>::at(unsigned int r, unsigned int c)
        {
            assert(r < rows_ && c < cols_);
            return data_(r * cols_ + c);
        }

        template <class T>
        T const& weak_matrix<T>::at(unsigned int r, unsigned int c) const
        {
            assert(r < rows_ && c < cols_);
            return data_(r * cols_ + c);
        }

        template <class T>
        vector_like<T>& weak_matrix<T>::as_vector()
        {
            return data_;
        }

        template <class T>
        vector_like<T> const& weak_matrix<T>::as_vector() const
        {
            return data_;
        }

        // tensor

        template <class T>
        tensor<T>::tensor()
            : data_(), sizes_(), dim_(0), mat_(data_.data(), 0, 0)
        {
        }

        template <class T>
        tensor<T>::tensor(tensor<T>&& that)
            : data_(std::move(that.data_)), sizes_(std::move(that.sizes_)), dim_(that.dim_)
            , mat_(data_.data(), sizes_.size() == 0 ? 0 : data_.size() / sizes_.back()
            , sizes_.size() == 0 ? 0 : sizes_.back())
        {}

        template <class T>
        tensor<T>::tensor(tensor<T> const& that)
            : tensor(that.as_vector(), that.sizes())
        {}

        template <class T>
        tensor<T>::tensor(tensor_like<T> const& that)
            : tensor(that.as_vector(), that.sizes())
        {}

        template <class T>
        tensor<T>::tensor(vector<T>&& data, std::vector<unsigned int> sizes)
            : data_(std::move(data)), sizes_(sizes), dim_(sizes_.size())
            , mat_(data_.data(), 0, 0)
        {
            for (int i = 0; i < sizes.size(); ++i) {
                assert(sizes[i] > 0);
            }

            if (dim_ != 0) {
                unsigned int d = 1;
                for (int i = 0; i < dim_; ++i) {
                    d *= sizes_[i];
                }

                assert(data_.size() == d);

                mat_ = weak_matrix<T>{data_.data(), d / sizes_.back(), sizes_.back()};
            } else {
                mat_ = weak_matrix<T>{data_.data(), 0, 0};
            }
        }

        template <class T>
        tensor<T>::tensor(vector_like<T> const& data, std::vector<unsigned int> sizes)
            : tensor(vector<T>(data), sizes)
        {}

        template <class T>
        tensor<T>::tensor(vector_like<T> const& v)
            : tensor(v, {v.size()})
        {}

        template <class T>
        tensor<T>::tensor(matrix_like<T> const& m)
            : tensor(weak_vector<T>(
                const_cast<double*>(m.data()), m.rows() * m.cols()), {m.rows(), m.cols()})
        {}

        template <class T>
        T* tensor<T>::data()
        {
            return data_.data();
        }

        template <class T>
        T const* tensor<T>::data() const
        {
            return data_.data();
        }

        template <class T>
        unsigned int tensor<T>::size(unsigned int d) const
        {
            return sizes_.at(d);
        }

        template <class T>
        T& tensor<T>::operator()(std::vector<int> indices)
        {
            assert(indices.size() == dim());

            unsigned int d = 0;

            for (int i = 0; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        T const& tensor<T>::operator()(std::vector<int> indices) const
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        T& tensor<T>::at(std::vector<int> indices)
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_.at(d);
        }

        template <class T>
        T const& tensor<T>::at(std::vector<int> indices) const
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_.at(d);
        }

        template <class T>
        void tensor<T>::resize(std::vector<unsigned int> new_sizes, T value)
        {
            for (int i = 0; i < new_sizes.size(); ++i) {
                assert(new_sizes[i] > 0);
            }

            if (new_sizes.size() == 0) {
                sizes_ = std::vector<unsigned int>();
                data_.resize(0);
                dim_ = 0;

                mat_ = weak_matrix<T>{data_.data(), 0, 0};
            } else {
                unsigned int d = 1;

                for (auto& s: new_sizes) {
                    d *= s;
                }

                sizes_ = new_sizes;
                data_.resize(d, value);

                dim_ = sizes_.size();

                mat_ = weak_matrix<T>{data_.data(), d / sizes_.back(), sizes_.back()};
            }
        }

        template <class T>
        tensor<T>& tensor<T>::operator=(tensor<T>&& that)
        {
            data_ = std::move(that.data_);
            dim_ = std::move(that.dim_);
            sizes_ = std::move(that.sizes_);
            mat_ = weak_matrix<T>(data_.data(), data_.size() / sizes_.back(), sizes_.back());

            return *this;
        }

        template <class T>
        tensor<T>& tensor<T>::operator=(tensor<T> const& that)
        {
            data_ = that.data_;
            dim_ = that.dim_;
            sizes_ = that.sizes_;
            mat_ = weak_matrix<T>(data_.data(), data_.size() / sizes_.back(), sizes_.back());

            return *this;
        }

        template <class T>
        unsigned int tensor<T>::dim() const
        {
            return dim_;
        }

        template <class T>
        unsigned int tensor<T>::vec_size() const
        {
            return data_.size();
        }

        template <class T>
        std::vector<unsigned int> tensor<T>::sizes() const
        {
            return sizes_;
        }

        template <class T>
        vector_like<T>& tensor<T>::as_vector()
        {
            return data_;
        }

        template <class T>
        vector_like<T> const& tensor<T>::as_vector() const
        {
            return data_;
        }

        template <class T>
        matrix_like<T>& tensor<T>::as_matrix()
        {
            return mat_;
        }

        template <class T>
        matrix_like<T> const& tensor<T>::as_matrix() const
        {
            return mat_;
        }

        // weak_tensor

        template <class T>
        weak_tensor<T>::weak_tensor(T *data,
            std::vector<unsigned int> sizes)
            : data_(data, 0), sizes_(sizes)
            , dim_(sizes_.size())
            , mat_(data, 0, 0)
        {
            for (int i = 0; i < sizes.size(); ++i) {
                assert(sizes[i] > 0);
            }

            if (dim_ != 0) {
                unsigned int d = 1;
                for (int i = 0; i < dim_; ++i) {
                    d *= sizes_[i];
                }

                data_ = weak_vector<T>{data, d};
                mat_ = weak_matrix<T>{data, d / sizes_.back(), sizes_.back()};
            } else {
                data_ = weak_vector<T>{data, 0};
                mat_ = weak_matrix<T>{data, 0, 0};
            }
        }

        template <class T>
        weak_tensor<T>::weak_tensor(tensor_like<T>& t)
            : weak_tensor(t.data(), t.sizes())
        {
        }

        template <class T>
        weak_tensor<T>::weak_tensor(vector_like<T> const& v)
            : weak_tensor(const_cast<T*>(v.data()), {v.size()})
        {
        }

        template <class T>
        weak_tensor<T>::weak_tensor(matrix_like<T> const& m)
            : weak_tensor(const_cast<T*>(m.data()), {m.rows(), m.cols()})
        {
        }

        template <class T>
        T* weak_tensor<T>::data()
        {
            return data_.data();
        }

        template <class T>
        T const* weak_tensor<T>::data() const
        {
            return data_.data();
        }

        template <class T>
        unsigned int weak_tensor<T>::size(unsigned int d) const
        {
            return sizes_.at(d);
        }

        template <class T>
        T& weak_tensor<T>::operator()(std::vector<int> indices)
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        T const& weak_tensor<T>::operator()(std::vector<int> indices) const
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        T& weak_tensor<T>::at(std::vector<int> indices)
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        T const& weak_tensor<T>::at(std::vector<int> indices) const
        {
            assert(indices.size() == dim());

            unsigned int d = indices.front();

            for (int i = 1; i < indices.size(); ++i) {
                d = d * sizes_.at(i) + indices.at(i);
            }

            return data_(d);
        }

        template <class T>
        unsigned int weak_tensor<T>::dim() const
        {
            return dim_;
        }

        template <class T>
        unsigned int weak_tensor<T>::vec_size() const
        {
            return data_.size();
        }

        template <class T>
        std::vector<unsigned int> weak_tensor<T>::sizes() const
        {
            return sizes_;
        }

        template <class T>
        vector_like<T>& weak_tensor<T>::as_vector()
        {
            return data_;
        }

        template <class T>
        vector_like<T> const& weak_tensor<T>::as_vector() const
        {
            return data_;
        }

        template <class T>
        matrix_like<T>& weak_tensor<T>::as_matrix()
        {
            return mat_;
        }

        template <class T>
        matrix_like<T> const& weak_tensor<T>::as_matrix() const
        {
            return mat_;
        }

        template <class T>
        matrix<T> trans(matrix_like<T> const& m)
        {
            matrix<T> result;
            result.resize(m.cols(), m.rows());

            for (int i = 0; i < m.rows(); ++i) {
                for (int j = 0; j < m.cols(); ++j) {
                    result(j, i) = m(i, j);
                }
            }

            return result;
        }

    }

}

namespace ebt {

    namespace json {
    
        template <class T>
        la::cpu::vector<T> json_parser<la::cpu::vector<T>>::parse(std::istream& is)
        {
            json_parser<std::vector<double>> vec_parser;
            return la::cpu::vector<T>(vec_parser.parse(is));
        }
    
        template <class T>
        la::cpu::matrix<T> json_parser<la::cpu::matrix<T>>::parse(std::istream& is)
        {
            json_parser<std::vector<std::vector<double>>> mat_parser;
            return la::cpu::matrix<T>(mat_parser.parse(is));
        }

        template <class T>
        la::cpu::tensor<T> json_parser<la::cpu::tensor<T>>::parse(std::istream& is)
        {
            json_parser<std::tuple<std::vector<int>, la::cpu::vector<T>>> parser;
            std::tuple<std::vector<int>, la::cpu::vector<T>> data = parser.parse(is);

            std::vector<unsigned int> sizes;

            for (auto& i: std::get<0>(data)) {
                sizes.push_back((unsigned int)(i));
            }

            return la::cpu::tensor<T>(std::move(std::get<1>(data)), sizes);
        }

        template <class T>
        void json_writer<la::cpu::vector<T>>::write(la::cpu::vector<T> const& v, std::ostream& os)
        {
            std::vector<T> vec {v.data(), v.data() + v.size()};
            ebt::json::json_writer<std::vector<T>> writer;
            writer.write(vec, os);
        }
    
        template <class T>
        void json_writer<la::cpu::matrix<T>>::write(la::cpu::matrix<T> const& m, std::ostream& os)
        {
            std::vector<std::vector<T>> mat;

            for (T const *i = m.data(); i < m.data() + m.rows() * m.cols(); i = i + m.cols()) {
                mat.push_back(std::vector<T> {i, i + m.cols()});
            }

            ebt::json::json_writer<std::vector<std::vector<T>>> writer;
            writer.write(mat, os);
        }

        template <class T>
        void json_writer<la::cpu::tensor<T>>::write(la::cpu::tensor<T> const& t, std::ostream& os)
        {
            std::tuple<std::vector<int>, la::cpu::vector<T>> data;

            unsigned int dim = 1;

            for (int i = 0; i < t.dim(); ++i) {
                std::get<0>(data).push_back(t.size(i));

                dim *= t.size(i);
            }

            std::get<1>(data) = la::cpu::vector<T>(la::cpu::weak_vector<T>(const_cast<T*>(t.data()), dim));

            ebt::json::json_writer<std::tuple<std::vector<int>, la::cpu::vector<T>>> writer;
            writer.write(data, os);
        }
    }
}
