#pragma once
#include <cassert>
#include <map>
#include <utility>
#include <vector>
#include <memory.h>

#ifndef safe_delete
#	define safe_delete(p) (delete(p), (p) = nullptr)
#endif

#ifndef safe_delete_array
#	define safe_delete_array(p) (delete[](p), (p) = nullptr)
#endif

// 一个表格中的全部指定数据
template<typename T>
class impl_grid_cell_values
{
public:
    impl_grid_cell_values() { reset_row_col_count(0, 0); }
    impl_grid_cell_values(int row_count, int col_count) { reset_row_col_count(row_count, col_count); }
    impl_grid_cell_values(const impl_grid_cell_values& src) { *this = src; }
    ~impl_grid_cell_values() { clear(); }

public:
    // 内部存储的数据直接对等，并不会判断是不是指针而决定使用深拷贝
    impl_grid_cell_values& operator=(const impl_grid_cell_values& src)
    {
        if (this == &src) return *this;

        clear();

        m_row_count = src.m_row_count;
        m_col_count = src.m_col_count;
        if (src.m_values)
        {
            int total_count = src.get_row_count() * src.get_col_count();
            m_values = new unsigned long long[total_count];
            for (int i = 0; i < total_count; ++i)
                m_values[i] = src.m_values[i];
        }

        m_value_in_row = src.m_value_in_row;
        m_value_in_col = src.m_value_in_col;
        m_value_order = src.m_value_order;
    }


public:
    // 判断是否是空表
    bool is_empty()
    {
        return (m_col_count < 1 || m_row_count < 1);
    }


    // 清空全部数据
    void clear()
    {
        int item_count = m_row_count * m_col_count;
        for (int i = 0; i < item_count; ++i)
            delete((T*)m_values[i]); // 不用再置空，稍后就全部删除了

        if(m_values)
            delete (m_values);
        m_values = nullptr;
        m_row_count = 0;
        m_col_count = 0;
        m_value_in_row.clear();
        m_value_in_col.clear();
        m_value_order.clear();
    }


    // 删除指定的数据行
    void delete_rows(int start_row, int count)
    {
        if (start_row >= m_row_count || count <= 0) return;

        if (start_row + count > m_row_count)
            count = m_row_count - start_row;

        int new_row_count = m_row_count - count;

        for (int i = start_row + count; i < m_row_count; ++i)
        {
            for (int j = 0; j < m_col_count; ++j)
            {
                int front_index = (i - count) * m_col_count + j;
                int back_index = i * m_col_count + j;

                unsigned long long old_ptr = m_values[front_index];
                m_values[front_index] = m_values[back_index];
                m_values[back_index] = old_ptr; // 把指针放回后面，以便稍后销毁指向的数据
            }
        }

        resize_row_col_count(new_row_count, m_col_count);
    }


    // 删除尾部的数据行
    void delete_rows_back(int count)
    {
        if (count <= 0) return;
        if (count > m_row_count) count = m_row_count;

        delete_rows(m_row_count - count, count);
    }


    // 删除首部的数据行
    void delete_rows_front(int count)
    {
        if (count <= 0) return;
        if (count >= m_row_count) count = m_row_count;

        delete_rows(0, count);
    }


    // 删除指定的数据列
    void delete_cols(int start_col, int count)
    {
        if (start_col >= m_col_count || count <= 0) return;

        if (start_col + count > m_col_count)
            count = m_col_count - start_col;

        int new_col_count = m_col_count - count;

        // 把数据先移到前面覆盖掉要删除的部分，再删除
        for (int i = 0; i < m_row_count; ++i)
        {
            for (int j = start_col + count; j < m_col_count; ++j)
            {
                int front_index = i * m_col_count + j - count;
                int back_index = i * m_col_count + j;

                unsigned long long old_ptr = m_values[front_index];
                m_values[front_index] = m_values[back_index];
                m_values[back_index] = old_ptr; // 把指针放回后面，以便稍后销毁指向的数据
            }
        }

        resize_row_col_count(m_row_count, new_col_count);
    }


    // 删除尾部的数据列
    void delete_cols_back(int count)
    {
        if (count <= 0) return;
        if (count > m_col_count) count = m_col_count;

        delete_cols(m_col_count - count, count);
    }


    // 删除首部的数据列
    void delete_cols_front(int count)
    {
        if (count <= 0) return;
        if (count >= m_col_count) count = m_col_count;

        delete_cols(0, count);
    }


    // 在指定的行之前插入足够多的行，下标小于0无效，下标比最后一行还要大，则新增的行放在最后
    void insert_rows(int row_index, int count)
    {
        if (row_index < 0 || count <= 0) return;

        int old_row_count = m_row_count;
        resize_row_col_count(m_row_count + count, m_col_count); // 更新了m_row_count
        if (row_index >= m_row_count) return;

        // 把数据往后移，把新插入的数据空出来
        // 如果是在最后插入的则不能移，否则越界了
        if (row_index < old_row_count)
        {
            for (int i = old_row_count - 1; i >= row_index; --i)
            {
                for (int j = 0; j < m_col_count; ++j)
                {
                    int front_index = i * m_col_count + j;
                    int back_index = (i + count) * m_col_count + j;

                    unsigned long long old_ptr = m_values[front_index];
                    m_values[front_index] = m_values[back_index];
                    m_values[back_index] = old_ptr;
                }
            }
        }
    }


    // 在首部之前插入足够多的行
    void insert_rows_front(int count)
    {
        insert_rows(0, count);
    }


    // 在尾部之后插入足够多的行
    void insert_rows_back(int count)
    {
        if (count <= 0) return;
        resize_row_col_count(m_row_count + count, m_col_count);
    }


    // 在指定的行之前插入足够多的列，下标小于0无效，下标比最后一列还要大，则新增的行放在最后
    void insert_cols(int col_index, int count)
    {
        if (col_index < 0 || count <= 0) return;

        int old_col_count = m_col_count;
        resize_row_col_count(m_row_count, m_col_count + count);
        if (col_index > m_col_count) return;

        // 把数据往后移，把新插入的数据空出来
        // 如果是在最后插入的则不能移，否则越界了
        if (col_index < old_col_count)
        {
            for (int i = 0; i < m_row_count; ++i)
            {
                for (int j = old_col_count - 1; j >= col_index; --j)
                {
                    int front_index = i * m_col_count + j;
                    int back_index = i * m_col_count + j + count;

                    unsigned long long old_ptr = m_values[front_index];
                    m_values[front_index] = m_values[back_index];
                    m_values[back_index] = old_ptr;
                }
            }
        }
    }


    // 在首部之前插入足够多的列
    void insert_cols_front(int count)
    {
        insert_cols(0, count);
    }


    // 在尾部之后插入足够多的列
    void insert_cols_back(int count)
    {
        if (count <= 0) return;
        resize_row_col_count(m_row_count, m_col_count + count);
    }


    // 重置数据为指定的行列数，内部倒数均会清空
    void reset_row_col_count(int row_count, int col_count)
    {
        clear();
        if (row_count <= 0 || col_count <= 0) return;

        m_values = new unsigned long long[row_count * col_count];
        memset(m_values, 0, row_count * col_count * sizeof(unsigned long long));

        m_row_count = row_count;
        m_col_count = col_count;
    }


    // 重新设置行列数，原有的数据会保留，新增的单元格会为nullptr（如果行或列上设置了数据，则会根据行或列设置数值）
    void resize_row_col_count(int row_count, int col_count)
    {
        if (m_row_count <= 0 || m_col_count <= 0)
        {
            reset_row_col_count(row_count, col_count);
            return;
        }

        if (row_count <= 0 || col_count <= 0)
        {
            clear();
            return;
        }

        int min_row_count = std::min(m_row_count, row_count);
        int min_col_count = std::min(m_col_count, col_count);

        // 复制原有数据
        unsigned long long* tmp_buffer = new unsigned long long[row_count * col_count];
        memset(tmp_buffer, 0, row_count * col_count * sizeof(unsigned long long));
        for (int i = 0; i < min_row_count; ++i)
            for (int j = 0; j < min_col_count; ++j)
                tmp_buffer[i * col_count + j] = m_values[i * m_col_count + j];

        // 销毁原来的数据中多出来的部分所指向的内容
        for (int i = min_row_count; i < m_row_count; ++i)
            for (int j = 0; j < min_col_count; ++j)
                delete((T*)m_values[i * m_col_count + j]); // 删除多出来的行（不含行列重叠部分）

        for (int i = 0; i < m_row_count; ++i)
            for (int j = min_col_count; j < m_col_count; ++j)
                delete((T*)m_values[i * m_col_count + j]); // 删除多出来的列（要包含行列重叠部分）

        // 指向的数据已经处理完毕，把数据数组指针删除（内容不删除）
        safe_delete_array(m_values);
        m_values = tmp_buffer;

        // 常规数据复制
        m_row_count = row_count;
        m_col_count = col_count;

        // 清理多出来的行列数据
        for (auto it = m_value_in_row.begin(); it != m_value_in_row.end(); /*nothing*/)
        {
            if (it->first >= row_count || it->first < 0)
                it = m_value_in_row.erase(it);
            else
                ++it;
        }

        for (auto it = m_value_in_col.begin(); it != m_value_in_col.end(); /*nothing*/)
        {
            if (it->first >= col_count || it->first < 0)
                it = m_value_in_col.erase(it);
            else
                ++it;
        }
    }


    int get_row_count() const
    {
        return m_row_count;
    }


    int get_col_count() const
    {
        return m_col_count;
    }


    // 只要行、列数不超过表格范围，则单元格实例没创建时就自动创建一个
    // 返回的是对象的引用，可直接修改内部数据
    const T& get_cell_value(int row, int col) const
    {
        assert(("grid is invalid", m_values != nullptr));
        assert(("row and col index is invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));
        assert(("row_count or col_count is invalid", m_row_count >= 0 && m_col_count >= 0));

        int idx = row * m_col_count + col;
        if (m_values[idx]) return *((const T*)(m_values[idx]));

        // const 函数内部也修改单元格的指针值，这里是出于对外提供const接口才这样处理的，以确保业务代码不搅入此逻辑
        T* tmp_cur_val_ptr = new T();
        m_values[idx] = (unsigned long long)tmp_cur_val_ptr;
        for (auto& x : m_value_order)
        {
            if (x.first != row || x.first != col) continue;

            if (x.second) // true为行
            {
                auto it = m_value_in_row.find(row);
                if (it != m_value_in_row.end())
                {
                    *(tmp_cur_val_ptr) = it->second;
                    break;
                }
            }
            else // false为列
            {
                auto it = m_value_in_col.find(col);
                if (it != m_value_in_col.end())
                {
                    *(tmp_cur_val_ptr) = it->second;
                    break;
                }
            }
        }

        return *((const T*)(m_values[idx]));
    }


    // 只要行、列数不超过表格范围，则单元格实例没创建时就自动创建一个
    // 返回的是对象的引用，可直接修改内部数据
    T& get_cell_value(int row, int col)
    {
        assert(("row and col index invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));

        const impl_grid_cell_values<T>* tmp_this = this;
        return const_cast<T&>(tmp_this->get_cell_value(row, col));
    }


    // 只要行、列数不超过表格范围，则单元格实例没创建时就自动创建一个
    // 返回的是对象的引用，可直接修改内部数据
    // 如果单元格没有数据，则会到最后设置的行或列上复制生成一个
    void get_cell_value(int row, int col, T& data) const
    {
        assert(("row and col index invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));
        data = get_cell_value(row, col);
    }


    // 仅当行、列数不超过表格范围，并且单元格实例已经生成时才会返回，否则返回空，如果要确保一定有实例，则可考虑
    // 使用get_cell_value或先使用set_cell_value接口，这个接口主要用于在不影响效率和内存占用的情况高效读取已
    // 有数据，返回的是内部对象的指针，可直接修改内部数据，内存仍由内部管理
    // 如果单元格没有数据，则不会查找行或列上的数据
    const T*  get_cell_value_when_exist(int row, int col) const
    {
        assert(("grid is invalid", m_values != nullptr));
        assert(("row and col index is invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));
        assert(("row_count or col_count is invalid", m_row_count >= 0 && m_col_count >= 0));

        int idx = row * m_col_count + col;
        if (!m_values[idx]) return nullptr;

        return ((const T*)((m_values[idx])));
    }


    // 行为同get_cell_value_when_exist接口，区别在于单元格上没有设置数据时会到最后设置的行列上找
    // 为防止误改行列的数据，此接口不直接返回对象的指针，而是外部构造好对象，内部复制返回
    void get_cell_value_when_exist_even_row_col(int row, int col, T& data) const
    {
        assert(("grid is invalid", m_values != nullptr));
        assert(("row and col index is invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));
        assert(("row_count or col_count is invalid", m_row_count >= 0 && m_col_count >= 0));

        int idx = row * m_col_count + col;
        if (m_values[idx]) data = *((const T*)(m_values[idx]));

        for (auto& x : m_value_order)
        {
            if (x.first != row && x.first != col) continue;

            if (x.second) // true为行
            {
                auto it = m_value_in_row.find(row);
                if (it != m_value_in_row.end())
                {
                    data = it->second;
                    break;
                }
            }
            else // false为列
            {
                auto it = m_value_in_col.find(col);
                if (it != m_value_in_col.end())
                {
                    data = it->second;
                    break;
                }
            }
        }
    }


    // 仅当行、列数不超过表格范围，并且单元格实例已经生成时才会返回，否则返回空，如果要确保一定有实例，则可考虑
    // 使用get_cell_value或先使用set_cell_value接口，这个接口主要用于在不影响效率和内存占用的情况高效读取已
    // 有数据，返回的是内部对象的指针，可直接修改内部数据，内存仍由内部管理
    T* get_cell_value_when_exist(int row, int col)
    {
        assert(("row and col index invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));

        const impl_grid_cell_values<T>* tmp_this = this;
        return const_cast<T*>(tmp_this->get_cell_value_when_exist(row, col));
    }


    void set_cell_value(int row, int col, const T& data)
    {
        assert(("row and col index invalid", row < m_row_count && row >= 0 && col < m_col_count && col >= 0));

        T& tmp_cell = get_cell_value(row, col);
        tmp_cell = data;
    }


    void set_row_value(int row, const T& data)
    {
        assert(("row index invalid", row < m_row_count && row >= 0));
        m_value_order.insert(m_value_order.begin(), {row, true});
        m_value_in_row[row] = data;

        // 把列全部更新，确保按列单元格取到的数据是最新的
        for (int i = 0; i < m_col_count; ++i)
            set_cell_value(row, i, data);
    }


    void get_row_value(int row, T& data)
    {
        assert(("row index invalid", row < m_row_count && row >= 0));

        auto it = m_value_in_row.find(row);
        if (it != m_value_in_row.end())
            data = it->second;
    }


    const T* get_row_value_when_exist(int row) const
    {
        assert(("row index invalid", row < m_row_count && row >= 0));

        auto it = m_value_in_row.find(row);
        if (it != m_value_in_row.end())
            return &(it->second);

        return nullptr;
    }


    T* get_row_value_when_exist(int row)
    {
        assert(("row index invalid", row < m_row_count && row >= 0));

        const impl_grid_cell_values<T>* tmp_this = this;
        return const_cast<T*>(tmp_this->get_row_value_when_exist(row));
    }


    void set_col_value(int col, const T& data)
    {
        assert(("col index invalid", col < m_col_count && col >= 0));
        m_value_order.insert(m_value_order.begin(), {col, false});

        m_value_in_col[col] = data;

        // 把行全部更新，确保按行单元格取到的数据是最新的
        for (int i = 0; i < m_row_count; ++i)
            set_cell_value(i, col, data);
    }


    void get_col_value(int col, T& data)
    {
        assert(("col index invalid", col < m_col_count && col >= 0));
        auto it = m_value_in_col.find(col);
        if (it != m_value_in_col.end())
            data = it->second;
    }


    const T* get_col_value_when_exist(int col) const
    {
        assert(("col index invalid", col < m_col_count && col >= 0));
        auto it = m_value_in_col.find(col);
        if (it != m_value_in_col.end())
            return &(it->second);

        return nullptr;
    }


    T* get_col_value_when_exist(int col)
    {
        assert(("col index invalid", col < m_col_count && col >= 0));

        const impl_grid_cell_values<T>* tmp_this = this;
        return const_cast<T*>(tmp_this->get_col_value_when_exist(col));
    }


private:
    int m_row_count = 0;
    int m_col_count = 0;
    unsigned long long* m_values = nullptr; // 这是一个多行多列的指针数组，每个元素是一个64位指针，指向T类型的数据对象

    std::map<int, T> m_value_in_row; // <行, 值>
    std::map<int, T> m_value_in_col; // <列, 值>
    std::vector<std::pair<int, bool>> m_value_order; // 记录行、列的数值设置先后顺序<<行或列号,true为行false为列>>,【0】号记录操作时间最晚，倒序存放
};
