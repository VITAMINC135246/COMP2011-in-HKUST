#include "img_2d_array.hpp"
#include <cstddef>
#include <iostream>

using namespace std;

/**
 * @brief Read a 2D array from an input.
 *
 * @param os Output to print prompt messages.
 * @param is Input to read a 2D array from.
 * @param dest 2D array to store the read input.
 * @param dest_height Reference to a `double` to store the 2D array height.
 * @param dest_width Reference to a `double` to store the 2D array width.
 */
void read_2d_array(double dest[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int &dest_height, int &dest_width)
{
    dest_height = INVALID_2D_ARRAY_SIZE;
    do
    {
        cout << "2D array height: ";
        cin >> dest_height;
        if (INVALID_2D_ARRAY_SIZE == dest_height || dest_height > MAX_2D_ARRAY_CAPACITY)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }
        break;
    } while (true);

    dest_width = INVALID_2D_ARRAY_SIZE;
    do
    {
        cout << "2D array width: ";
        cin >> dest_width;
        if (INVALID_2D_ARRAY_SIZE == dest_width || dest_width > MAX_2D_ARRAY_CAPACITY)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }
        break;
    } while (true);

    int data_size = dest_height * dest_width;
    bool success = 0;
    do
    {
        cout << "2D array data (" << data_size << " numbers expected):\n";
        success = true;
        for (int idx = 0; idx < data_size; ++idx)
        {
            int quot = idx / dest_width;
            int rem = idx % dest_width;
            cin >> dest[quot][rem];
            if (!cin)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input!\n";
                success = false;
                break;
            }
        }
    } while (!success);
}

/**
 * @brief Copy a 2D array from another 2D array.
 *
 * @note Task 1: Implement this function.
 *
 * All 2D arrays are properly allocated and their sizes are valid.
 * The `src` 2D array contains initialized data within the specified height and width.
 * You do not need to set values of `dest` that are outside the specified height and width.
 *
 * To copy the 2D array, you can use two `for`-loops, the inner loop being inside the other loop.
 * The outer loop iterates through each row from 0 (inclusive) to height (exclusive).
 * The inner loop iterates through each cell in a row from 0 (inclusive) to width (exclusive)
 * and copies the value in that cell from `src` to `dest`.
 *
 * Remember that 2D arrays have row-major order, so you access a cell using `array[y][x]`.
 * Also remember to copy the 2D array height and width as well.
 *
 * @param dest 2D array to be copied to.
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src 2D array to be copied from.
 * @param src_height Height of the 2D array to be copied from.
 * @param src_width Width of the 2D array to be copied from.
 */
void copy_2d_array(double dest[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int &dest_height, int &dest_width,
                   const double src[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int src_height, int src_width)
{
    for (int i = 0; i < src_height; i++)
    {
        for (int j = 0; j < src_width; j++)
        {
            dest[i][j] = src[i][j];
        }
    }

    dest_height = src_height;
    dest_width = src_width;
}

/**
 * @brief Print a 2D array to `cout`.
 *
 * @param src 2D array to be printed.
 * @param src_height Height of the 2D array to be printed.
 * @param src_width Width of the 2D array to be printed.
 */
void print_2d_array(const double src[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int src_height, int src_width)
{
    // Do NOT change the code below!
    if (src_height == INVALID_2D_ARRAY_SIZE || src_width == INVALID_2D_ARRAY_SIZE)
    {
        cout << "Invalid array!\n";
        return;
    }

    cout << '[';
    for (int yy = 0; yy < src_height; ++yy)
    {
        cout << (yy > 0 ? " [" : "[");
        for (int xx = 0; xx < src_width; ++xx)
        {
            if (xx > 0)
                cout << ' ';
            cout << src[yy][xx];
        }
        cout << (yy + 1 < src_height ? "]\n" : "]");
    }
    cout << "]\n";
}

/**
 * @brief Broadcast two sizes from two 2D arrays in the same dimension.
 *
 * @note Task 2: Implement this function.
 *
 * All sizes are valid. That means you do not need to handle invalid sizes.
 *
 * To broadcast two sizes in the same dimension,
 * first check if the two sizes are the same. If so, that is the broadcasted size.
 * Otherwise, check if one of the sizes is 1. If so, the other size is the broadcasted size.
 * (What if both sizes are 1?)
 * Otherwise, these two sizes cannot be broadcasted. Return `INVALID_2D_ARRAY_SIZE`.
 * (Another thing to consider: What if one of the sizes is 0? Or both are 0?)
 *
 * @param left Size in a dimension of the left 2D array.
 * @param right Size in the same dimension of the right 2D array.
 * @return int Broadcasted size for the two 2D arrays in that dimension.
 *
 * If they cannot be broadcasted, `INVALID_2D_ARRAY_SIZE` is returned.
 */
int broadcast_size(int left, int right)
{

    if (left == right)
    {
        return left;
    }
    else if (left == 1)
    {
        return right;
    }
    else if (right == 1)
    {
        return left;
    }
    else
    {
        return INVALID_2D_ARRAY_SIZE;
    }
}

/**
 * @brief Broadcast two 2D arrays and get its resulting size. Also checks if the two 2D arrays can be broadcasted.
 *
 * @note Task 3: Implement this function.
 *
 * All 2D array sizes are valid. That means you do not need to handle invalid sizes.abort
 *
 * For two 2D array to be broadcastable, all of their dimensions, i.e. height and width, are broadcastable.
 * If the two 2D arrays are broadcastable, write the broadcasted 2D array size to `dest_height` and `dest_width`.
 * Otherwise, write `INVALID_2D_ARRAY_SIZE` to both `dest_height` and `dest_width`.
 *
 * Remember to also return a `bool` representing if the two 2D arrays are broadcastable.
 *
 * You are recommended to use `broadcast_size` to implement this function.
 *
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src_left_height Height of the left 2D array.
 * @param src_left_width Width of the left 2D array.
 * @param src_right_height Height of the right 2D array.
 * @param src_right_width Width of the right 2D array.
 * @return true If the two 2D arrays can be broadcasted.
 * @return false If the two 2D arrays cannot be broadcasted.
 */
bool broadcast_2d_size(int &dest_height, int &dest_width,
                       int src_left_height, int src_left_width,
                       int src_right_height, int src_right_width)
{
    int h = broadcast_size(src_left_height, src_right_height);
    int w = broadcast_size(src_left_width, src_right_width); // store the result first;

    if (h == INVALID_2D_ARRAY_SIZE || w == INVALID_2D_ARRAY_SIZE)
    {
        dest_height = INVALID_2D_ARRAY_SIZE;
        dest_width = INVALID_2D_ARRAY_SIZE;

        return false;}

    else{
        dest_height = h;
        dest_width = w;
        return true;
}
}

/**
 * @brief Perform an arithmetic operation on two 2D arrays element-wise. The two 2D arrays are broadcasted if possible.
 *
 * @note Task 4: Implement this function.
 *
 * Do not be overwhelmed by the number of parameters!
 * Try to group a 2D array and its sizes as a single parameter in your mind,
 * e.g. consider `dest`, `dest_height`, `dest_width` as a single parameter.
 * Later, when you learn structs, you can understand how structs
 * can group parameters together to make the function more readable.
 *
 * All 2D arrays are properly allocated and their sizes are valid.
 * The `src_left` and `src_right` 2D arrays contain initialized data within the specified height and width.
 * You do not need to set values of `dest` that are outside the specified height and width.
 *
 * To implement this function, check if the two 2D arrays can be broadcasted.
 * If not, write `INVALID_2D_ARRAY_SIZE` to both `dest_height` and `dest_width`,
 * and return `false`. You are recommended to use `broadcast_2d_size`.
 *
 * Otherwise, perform the arithmetic operation specified by `op` element-wise,
 * broadcasting as needed. The lab introduction should give you an idea how broadcasting works.
 * A hint for calculating the indices when implementing broadcasting:
 * Consider iterating through each cell of `dest` first, using two nested loops.
 * You should know the height and width of `dest` fromm `broadcast_2d_size`.
 * Then, consider the current coordinate `dest[y][x]` of `dest`.
 * You can calculate the two corresponding coordinates in `src_left` and `src_right`
 * from the current coordinate in `dest`. Make use of the fact that broadcasting is
 * only relevant when the size of a dimension in one of the two 2D arrays is 1.
 * After calculating the two correspondng coordinates,
 * simply perform the requested arithmetic operation using the three coordinates above.
 *
 * The arithmetic operations are to be performed as follows:
 *
 * - `ADD` (+): `dest = left + right`
 *
 * - `SUBTRACT` (-): `dest = left - right`
 *
 * - `MULTIPLY` (*): `dest = left * right`
 *
 * - `DIVIDE` (/): If `right` is 0, `dest = 0`. Otherwise, `dest = left / right`.
 *
 * Remember that 2D arrays have row-major order, so you access a cell using `array[y][x]`.
 * Also remember to set the result 2D array height and width as well.
 *
 * Finally, return `true` to indicate that broadcasting and
 * the above element-wise arithmetic operation is successful.
 *
 * @param op Arithmetic operation to be performed on two 2D arrays.
 * @param dest 2D array to store the calculation result.
 * @param dest_height Reference to a variable to store the 2D array height.
 * @param dest_width Reference to a variable to store the 2D array width.
 * @param src_left 2D array on the left of the arithmetic operation.
 * @param src_left_height Height of the left 2D array.
 * @param src_left_width Width of the left 2D array.
 * @param src_right 2D array on the right of the arithmetic operation.
 * @param src_right_height Height of the right 2D array.
 * @param src_right_width Width of the right 2D array.
 * @return true If the two 2D arrays can be broadcasted and the arithmetic operation succeeded.
 * @return false If the two 2D arrays cannot be broadcasted.
 */
bool oper_2d_array(ops_2d_array op,
                   double dest[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int &dest_height, int &dest_width,
                   const double src_left[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int src_left_height, int src_left_width,
                   const double src_right[MAX_2D_ARRAY_CAPACITY][MAX_2D_ARRAY_CAPACITY], int src_right_height, int src_right_width)
{
    // step 1: check it can be broadcasted or not, exclude the situation of invalid broadcasting 2-d array.
    if (!broadcast_2d_size(dest_height, dest_width, src_left_height, src_left_width, src_right_height, src_right_width))
    {
        dest_height = INVALID_2D_ARRAY_SIZE;
        dest_width = INVALID_2D_ARRAY_SIZE;
        return false;
    }

    // main logic if the content of 2-d array is valid for broadcasting:
    for (int y = 0; y < dest_height; ++y)
    {
        for (int x = 0; x < dest_width; ++x)
        {
            // basic idea is: dest[y][x] = left_value +-*/ right_value; value at left or right needs a specific "coordinates" at certain arry;
            // so first, create the local variable left_value + right value, check its validness, and finally determine its value
            // because the array might be broadcasted!!!!! after broadcasting, we dont need to create a new array, just need to quote the value in original array correctly.

            int left_value_h = (src_left_height == 1) ? 0 : y;
            int left_value_w = (src_left_width == 1) ? 0 : x;
            int right_value_h = (src_right_height == 1) ? 0 : y;
            int right_value_w = (src_right_width == 1) ? 0 : x;
            // if broadcasting as the orginal array's w or h is 1, then just need quote this value.

            double left_value = src_left[left_value_h][left_value_w];
            double right_value = src_right[right_value_h][right_value_w];
            //"coordinates" to determine value that will use in operation.

            switch (op)
            {
            case ADD:
                dest[y][x] = left_value + right_value;
                break;
            case SUBTRACT:
                dest[y][x] = left_value - right_value;
                break;
            case MULTIPLY:
                dest[y][x] = left_value * right_value;
                break;
            case DIVIDE:
                dest[y][x] = (right_value == 0.0) ? 0.0 : left_value / right_value;
                break;

            default:
                cout << "please input the correct operation sign!" << endl;
            }
        }
    }
    return true;
}
