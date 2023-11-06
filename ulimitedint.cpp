/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt(){};

UnlimitedInt::UnlimitedInt(string s)
{
    if (s == "0" || s == "-0")
    {
        sign = 0;
        size = 1;
        capacity = 1;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
    }
    else if (s[0] != '-')
    {
        while (s[0] == '0')
        {
            s.erase(s.begin());
        }
        capacity = s.size();
        size = capacity;
        sign = 1;
        unlimited_int = new int[capacity];
        for (int i = 0; i < s.size(); i++)
        {

            switch (s[i])
            {
            case '0':
                unlimited_int[i] = 0;
                break;
            case '1':
                unlimited_int[i] = 1;
                break;
            case '2':
                unlimited_int[i] = 2;
                break;

            case '3':
                unlimited_int[i] = 3;
                break;

            case '4':
                unlimited_int[i] = 4;
                break;

            case '5':
                unlimited_int[i] = 5;
                break;

            case '6':
                unlimited_int[i] = 6;
                break;

            case '7':
                unlimited_int[i] = 7;
                break;

            case '8':
                unlimited_int[i] = 8;
                break;

            case '9':
                unlimited_int[i] = 9;
                break;

            default:
                break;
            }
        }
    }
    else if (s[0] == '-')
    {
        while (s[1] == '0')
        {
            s.erase(s.begin() + 1);
        }
        capacity = s.size() - 1;
        size = capacity;
        sign = -1;
        unlimited_int = new int[capacity];
        for (int i = 0; i < capacity; i++)
        {

            switch (s[capacity - i])
            {
            case '0':
                unlimited_int[capacity - i - 1] = 0;
                break;
            case '1':
                unlimited_int[capacity - i - 1] = 1;
                break;
            case '2':
                unlimited_int[capacity - i - 1] = 2;
                break;

            case '3':
                unlimited_int[capacity - i - 1] = 3;
                break;

            case '4':
                unlimited_int[capacity - i - 1] = 4;
                break;

            case '5':
                unlimited_int[capacity - i - 1] = 5;
                break;

            case '6':
                unlimited_int[capacity - i - 1] = 6;
                break;

            case '7':
                unlimited_int[capacity - i - 1] = 7;
                break;

            case '8':
                unlimited_int[capacity - i - 1] = 8;
                break;

            case '9':
                unlimited_int[capacity - i - 1] = 9;
                break;

            default:
                break;
            }
        }
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    if (i == 0)
    {
        size = 1;
        sign = 0;
        capacity = size;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
    }
    else if (i < 0)
    {
        sign = -1;
        int j = i * -1;
        int k = j;
        int n = j;
        size = 0;
        while (k != 0)
        {
            k = k / 10;
            size++;
        }

        capacity = size;
        unlimited_int = new int[capacity];
        for (int rand = 0; rand < capacity; rand++)
        {
            unlimited_int[capacity - rand - 1] = n % 10;
            n = n / 10;
        }
    }
    else if (i > 0)
    {
        sign = 1;
        int k = i;
        int n = i;
        size = 0;
        while (k != 0)
        {
            size++;
            k = k / 10;
        }

        capacity = size;
        unlimited_int = new int[capacity];
        for (int rand = 0; rand < capacity; rand++)
        {
            unlimited_int[capacity - rand - 1] = n % 10;
            n = n / 10;
        }
    }
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{

    int i = 0;
    while (ulimited_int[i] == 0)
    {
        i = i + 1;
    }
    if (i == cap)
    {
        size = 1;
        capacity = 1;
        sign = 0;
        unlimited_int = new int[capacity];
        unlimited_int[0] = 0;
    }
    else
    {
        size = sz - i;
        capacity = cap - i;
        unlimited_int = new int[capacity];
        sign = sgn;
        for (int k = 0; k < capacity; k++)
        {
            unlimited_int[capacity - k - 1] = ulimited_int[cap - k - 1];
        }
    }
};

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
    unlimited_int = nullptr;
};

int UnlimitedInt::get_size()
{
    return size;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int cap;
    if (i1->get_sign() == 1 && i2->get_sign() == 1)
    {
        if (i1->get_capacity() >= i2->get_capacity())
        {
            cap = i1->get_capacity();
            int *res = new int[cap];
            int carry = 0;
            for (int i = 0; i < i2->get_capacity(); i++)
            {
                int ans = arr1[i1->get_capacity() - i - 1] + arr2[i2->get_capacity() - i - 1] + carry;
                res[cap - i - 1] = ans % 10;
                carry = ans / 10;
            }
            if (i1->get_capacity() != i2->get_capacity())
            {
                for (int i = i2->get_capacity(); i < cap; i++)
                {
                    int ans = arr1[i1->get_capacity() - i - 1] + carry;
                    res[cap - i - 1] = ans % 10;
                    carry = ans / 10;
                }
            }
            if (carry == 0)
            {
                UnlimitedInt *result = new UnlimitedInt(res, cap, 1, cap);
                return result;
            }
            else
            {
                int *res2 = new int[cap + 1];
                for (int i = 0; i < cap; i++)
                {
                    res2[cap - i] = res[cap - i - 1];
                }
                res2[0] = carry;
                cap++;
                delete res;
                UnlimitedInt *result = new UnlimitedInt(res2, cap, 1, cap);
                return result;
            }
        }
        else if (i1->get_capacity() < i2->get_capacity())
        {
            cap = i2->get_capacity();
            int *res = new int[cap];
            int carry = 0;
            for (int i = 0; i < i1->get_capacity(); i++)
            {
                int ans = arr1[i1->get_capacity() - i - 1] + arr2[i2->get_capacity() - i - 1] + carry;
                res[cap - i - 1] = ans % 10;
                carry = ans / 10;
            }
            for (int i = i1->get_capacity(); i < cap; i++)
            {
                int ans = arr2[i2->get_capacity() - i - 1] + carry;
                res[cap - i - 1] = ans % 10;
                carry = ans / 10;
            }
            if (carry == 0)
            {
                UnlimitedInt *result = new UnlimitedInt(res, cap, 1, cap);
                return result;
            }
            else
            {
                int *res2 = new int[cap + 1];
                for (int i = 0; i < cap; i++)
                {
                    res2[cap - i] = res[cap - i - 1];
                }
                res2[0] = carry;
                cap++;
                delete res;
                UnlimitedInt *result = new UnlimitedInt(res2, cap, 1, cap);
                return result;
            }
        }
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = add(i3, i4);
        UnlimitedInt *res2 = new UnlimitedInt(res->get_array(), res->get_capacity(), -1, res->get_size());
        // delete res;
        delete i3;
        delete i4;
        return res2;
    }
    else if (i1->get_sign() == 1 && i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = sub(i1, i3);
        // delete i3;
        return res;
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == 1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *res = sub(i2, i3);
        // delete i3;
        return res;
    }
    else if (i1->get_sign() == 0)
    {
        return new UnlimitedInt(i2->to_string());
    }
    else if (i2->get_sign() == 0)
    {
        return new UnlimitedInt(i1->to_string());
    }
};

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();
    int cap;
    if (i1->get_sign() == 1 && i2->get_sign() == 1)
    {
        if (i1->get_capacity() >= i2->get_capacity())
        {
            if (i1->to_string() == i2->to_string())
            {
                return new UnlimitedInt(0);
            }
            cap = i1->get_capacity();
            int *res = new int[cap];
            int carry = 0;
            for (int i = 0; i < i2->get_capacity(); i++)
            {
                int ans = arr1[i1->get_capacity() - i - 1] - arr2[i2->get_capacity() - i - 1] - carry;
                res[cap - i - 1] = (ans + 10) % 10;
                if (ans < 0)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
            }

            for (int i = i2->get_capacity(); i < cap; i++)
            {
                int ans = arr1[i1->get_capacity() - i - 1] - carry;
                res[cap - i - 1] = (ans + 10) % 10;
                if (ans < 0)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
            }
            if (carry == 1)
            {

                UnlimitedInt *res2 = new UnlimitedInt(sub(i2, i1)->get_array(), cap, -1, cap);
                return res2;
            }
            int i = 0;
            while (res[i] == 0)
            {
                i++;
            }
            if (i == cap)
            {
                UnlimitedInt *result = new UnlimitedInt(0);
                return result;
            }
            UnlimitedInt *result = new UnlimitedInt(res, cap, 1, cap);
            return result;
        }
        else if (i1->get_capacity() < i2->get_capacity())
        {
            int newCap = i2->get_capacity();
            int *res = new int[newCap];
            UnlimitedInt *temp;
            temp = sub(i2, i1);
            for (int i = 0; i < newCap; i++)
            {
                res[i] = temp->get_array()[i];
            }
            UnlimitedInt *result = new UnlimitedInt(res, newCap, -1, newCap);
            return result;
        }
    }
    else if (i1->get_sign() == 1 && i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = add(i1, i3);
        // delete i3;
        return res;
    }
    else if (i2->get_sign() == 1 && i1->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -1, i2->get_size());
        UnlimitedInt *res = add(i1, i3);
        // delete i3;
        return res;
    }
    else if (i1->get_sign() == -1 && i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *res = sub(i3, i4);
        // delete i3;
        // delete i4;
        return res;
    }
    else if (i1->get_sign() == 0)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -1 * i2->get_sign(), i2->get_size());
        return i3;
    }
    else if (i2->get_sign() == 0)
    {
        return new UnlimitedInt(i1->to_string());
    }
};

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{

    int *arr1 = i1->get_array();
    int *arr2 = i2->get_array();

    if (i1->get_sign()==1 && i2->get_sign()==1){
        int cap = i1->get_capacity() + i2->get_capacity();
        int* res = new int[cap];
        for (int t = 0;t<cap;t++){
            res[t]=0;
        }
        for (int i = i1->get_capacity()-1; i>=0;i--){
            for(int j =i2->get_capacity()-1;j>=0;j--){
                int a = arr1[i] * arr2[j] + res[i+j+1];
                res[i+j+1] = a%10;
                res[i+j] += a/10;
            }
        }
        UnlimitedInt* result = new UnlimitedInt(res,cap,1,cap);
        return result;
    }
    else if (i1->get_sign() == -1 and i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = mul(i3, i4);
        // delete i3;
        // delete i4;
        return res;
    }
    else if (i1->get_sign() * i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = mul(i3, i4);
        UnlimitedInt *res2 = new UnlimitedInt(res->get_array(), res->get_capacity(), -1, res->get_size());
        delete i3;
        delete i4;
        // delete res;
        return res2;
    }
    else if (i1->get_sign() * i2->get_sign() == 0)
    {
        UnlimitedInt *zero = new UnlimitedInt(0);
        return zero;
    }
};

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() == 1 && i2->get_sign() == 1)
    {
        if (i1->get_sign() == 0)
        {
            return new UnlimitedInt(0);
        }
        if (i1->get_capacity() < i2->get_capacity())
        {
            UnlimitedInt *res = new UnlimitedInt(0);
            return res;
        }
        else
        {
            string res = "";
            string s1 = "";
            int a = i2->get_capacity();
            for (int i = 0; i < i2->get_capacity(); i++)
            {
                s1.push_back(i1->to_string()[i]);
            }

            int division = 0;
            UnlimitedInt *temp = new UnlimitedInt(s1);
            while (sub(temp, i2)->get_sign() != -1)
            {
                division++;
                temp = sub(temp, i2);
            }
            // first div and first remainder
            s1 = temp->to_string();
            res.push_back(division + '0');
            // cout << res << endl;
            // updated s1 and first res
            // correct till here
            for (int i = a; i < i1->get_capacity(); i++)
            {
                division = 0;
                if (s1 == "0")
                {
                    s1.clear();
                }
                s1.push_back(i1->to_string()[i]);
                UnlimitedInt *temp2 = new UnlimitedInt(s1);
                //delete temp;
                temp = temp2;
                // cout << temp->to_string() << endl;
                // cout << i2->to_string() << endl;
                while (sub(temp, i2)->to_string()[0] != '-')
                {

                    division++;
                    // cout << division << "papita" << endl;
                    s1 = sub(temp, i2)->to_string();
                    UnlimitedInt *temp2 = new UnlimitedInt(s1);
                    //delete temp;
                    temp = temp2;
                    if (temp->to_string() == i2->to_string())
                    {
                        division++;
                        break;
                    }
                }
                s1 = temp->to_string();
                res.push_back(division % 10 + '0');
            }
            UnlimitedInt *ans = new UnlimitedInt(res);
            return ans;
        }
    }
    else if (i1->get_sign()==-1 && i2->get_sign()==-1){
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res =div(i3, i4);
        // delete i3;
        // delete i4;
        return res;
    }
    else if (i1->get_sign() * i2->get_sign() == -1)
    {
        UnlimitedInt *i3 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
        UnlimitedInt *i4 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
        UnlimitedInt *res = div(i3, i4);
        UnlimitedInt *res2 = new UnlimitedInt(res->get_array(), res->get_capacity(), -1, res->get_size());
        delete i3;
        delete i4;
        // delete res;
        return res2;
    }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{

    UnlimitedInt *quotient = new UnlimitedInt(div(i1, i2)->to_string());
    // cout<<quotient->to_string()<<" this is quotient."<<endl;
    UnlimitedInt *subtractor = new UnlimitedInt(mul(i2, quotient)->to_string());
    // cout<<subtractor->to_string()<<" this subtractor."<<endl;
    UnlimitedInt *result = new UnlimitedInt(sub(i1, subtractor)->to_string());
    return result;
};

string UnlimitedInt::to_string()
{
    string res;
    if (sign == -1)
    {
        res.push_back('-');
    }
    for (int i = 0; i < capacity; i++)
    {

        switch (unlimited_int[i])
        {
        case 0:
            res.push_back('0');
            break;
        case 1:
            res.push_back('1');
            break;
        case 2:
            res.push_back('2');
            break;

        case 3:
            res.push_back('3');
            break;

        case 4:
            res.push_back('4');
            break;

        case 5:
            res.push_back('5');
            break;

        case 6:
            res.push_back('6');
            break;

        case 7:
            res.push_back('7');
            break;

        case 8:
            res.push_back('8');
            break;

        case 9:
            res.push_back('9');
            break;

        default:
            break;
        }
    }

    return res;
}

// int main()
// {
//     UnlimitedInt *i1 = new UnlimitedInt("56");
//     UnlimitedInt *i2 = new UnlimitedInt("21");
//     UnlimitedInt *i3 = new UnlimitedInt("003");
//     cout << i1->mul(i1, i2)->to_string() << endl;
//     //   cout<< i3->to_string()<<endl;
//     //cout << i2->mul(i2, i1)->to_string() << endl;
// }
