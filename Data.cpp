#include "Data.h"
#include <limits>
#include <iostream>
void reverseIntBytes(int& num)
{
    int NO_OF_BYTES = sizeof(num);
    int reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BYTES; i++) {
        int temp = (255 << 8 * i) & num;
        reverse_num |= temp >> 8 * i << 8 * (NO_OF_BYTES - i - 1);
    }
    num = reverse_num;

}


bool Data::open(const string& imf, const string& lbf)
{
    imageFileName = imf;
    labelFileName = lbf;
    imageIn.open(imageFileName, std::ios_base::in | std::ios_base::binary);
    labelIn.open(labelFileName, std::ios_base::in | std::ios_base::binary);
    if (good())
    {
        int magicNum = -1;
        imageIn.read((char*)&magicNum, 4); reverseIntBytes(magicNum);//for check
        imageIn.read((char*)&m_size, 4); reverseIntBytes(m_size);
        imageIn.read((char*)&numOfRow, 4); reverseIntBytes(numOfRow);
        imageIn.read((char*)&numOfColumn, 4); reverseIntBytes(numOfColumn);
        picSize = numOfRow * numOfColumn;
        return true;
    }
    else
    {
        m_size = numOfRow = numOfColumn = picSize = -1;
        return false;
    }
}


Data::Data(const string& imf, const string& lbf) : imageFileName(imf), labelFileName(lbf)
{
    imageFileName = imf;
    labelFileName = lbf;
    imageIn.open(imageFileName, std::ios_base::in | std::ios_base::binary);
    labelIn.open(labelFileName, std::ios_base::in | std::ios_base::binary);
    if (good())
    {
        int magicNum = -1;
        imageIn.read((char*)&magicNum, 4); reverseIntBytes(magicNum);//for check
        imageIn.read((char*)&m_size, 4); reverseIntBytes(m_size);
        imageIn.read((char*)&numOfRow, 4); reverseIntBytes(numOfRow);
        imageIn.read((char*)&numOfColumn, 4); reverseIntBytes(numOfColumn);
        picSize = numOfRow * numOfColumn;
    }
    else
    {
        m_size = numOfRow = numOfColumn = picSize = -1;
    }
}

int Data::size() const
{
    return m_size;
}

std::pair<Linear::RowVector, Linear::RowVector> Data::operator[](int index)
{
    std::pair<Linear::RowVector, Linear::RowVector> out;
    out.first.assign(numOfColumn * numOfRow, 0.0);
    out.second.assign(10, 0.0);
    uint8_t input = 0;
    labelIn.seekg(8 + index);
    labelIn.read((char*)&input, sizeof(uint8_t));
    out.second[input] = 1.0;
    imageIn.seekg(16 + picSize * index);
    for (int i = 0; i < picSize; ++i)
    {
        imageIn.read((char*)&input, sizeof(uint8_t));
        out.first[i] = double(input) / double(std::numeric_limits<uint8_t>::max());
    }
    return out;

}

bool Data::good() const
{
    return imageIn.is_open()&&labelIn.is_open();
}

void Visualize::show(const Linear::RowVector& m, int row, int col)
{
    using namespace std;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (m[i * col + j] > 0.5)
                cout << "**";
            else
                cout << "  ";
        }
        cout << endl;
    }
}