/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"


UnlimitedInt *GCD(UnlimitedInt *i1, UnlimitedInt *i2)
{

    if (i1->get_sign() == 0)
    {
        return new UnlimitedInt(i2->to_string());
    }
    if (i2->get_sign() == 0)
    {
        return new UnlimitedInt(i1->to_string());
    }
    if (i1->sub(i1, i2)->get_sign() == 0)
    {
        return new UnlimitedInt(i1->to_string());
    }
    if (i1->sub(i1, i2)->get_sign() == 1)
    {
        UnlimitedInt *temp = new UnlimitedInt(i1->mod(i1, i2)->to_string());
        // cout<<temp->to_string()<<endl;
        return GCD(temp,i2);
    }
    if (i1->sub(i1, i2)->get_sign() == -1)
    {
        UnlimitedInt *temp = new UnlimitedInt(i1->mod(i2, i1)->to_string());
        // cout<<temp->to_string()<<endl;
        return GCD(i1,temp);
    }
};
UnlimitedRational::UnlimitedRational()
{
    p = nullptr;
    q = nullptr;
};

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    if (num->get_sign() == den->get_sign())
    {
        // UnlimitedInt *one = new UnlimitedInt(1);
        // UnlimitedInt *zero = new UnlimitedInt(0);
        if(den->get_sign()==0){
            p = new UnlimitedInt(0);
            q = new UnlimitedInt(0);
        }
        if (num->get_sign() == 0)
        {
            p = new UnlimitedInt(0);
            q = new UnlimitedInt(1);
        }

        else if (num->sub(num, den)->get_sign() == 0)
        {

            p = new UnlimitedInt(1);
            q = new UnlimitedInt(1);
        }
        else
        {
            UnlimitedInt *temp = GCD(num, den);
            UnlimitedInt *temp2 = temp->div(num, temp);
            UnlimitedInt *temp3 = temp->div(den, temp);
            p = new UnlimitedInt(temp2->get_array(), temp2->get_capacity(), 1, temp2->get_size());
            q = new UnlimitedInt(temp3->get_array(), temp3->get_capacity(), 1, temp3->get_size());
            // delete temp3;
            // delete temp2;
            // delete temp;
        }
    }

    else if (num->get_sign() != den->get_sign())
    {
        UnlimitedInt *num1 = new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size());
        UnlimitedInt *den1 = new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size());
        // UnlimitedInt *one = new UnlimitedInt(1);
        // UnlimitedInt *zero = new UnlimitedInt(0);
        if (num1->get_sign() == 0)
        {
            p = new UnlimitedInt(0);
            q = new UnlimitedInt(1);
        }

        else if (num1->sub(num1, den1)->get_sign() == 0)
        {

            p = new UnlimitedInt(1);
            q = new UnlimitedInt(1);
        }
        else
        {
            UnlimitedInt *temp = GCD(num1, den1);
            UnlimitedInt *temp2 = temp->div(num1, temp);
            UnlimitedInt *temp3 = temp->div(den1, temp);
            p = new UnlimitedInt(temp2->get_array(), temp2->get_capacity(), -1, temp2->get_size());
            q = new UnlimitedInt(temp3->get_array(), temp3->get_capacity(), 1, temp3->get_size());
            // delete temp3;
            // delete temp2;
            // delete num1;
            // delete den1;
            // delete temp;
        }
    }
};

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
};

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
};

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
};

string UnlimitedRational::get_p_str()
{
    return p->to_string();
};

string UnlimitedRational::get_q_str()
{
    return q->to_string();
};

string UnlimitedRational::get_frac_str()
{
    string s = p->to_string() + "/" + q->to_string();
    return s;
};

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();
    UnlimitedInt *num = p1->add(p1->mul(p1, q2), q1->mul(q1, p2));
    // cout<<num->to_string()<<endl;
    UnlimitedInt *den = q1->mul(q1, q2);
    // cout<<den->to_string()<<endl;
    UnlimitedRational *res = new UnlimitedRational(num, den);
    // delete p1;
    // delete p2;
    // delete q1;
    // delete q2;
    return res;
};

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();
    UnlimitedInt *num = p1->sub(p1->mul(p1, q2), q1->mul(q1, p2));
    UnlimitedInt *den = q1->mul(q1, q2);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    // delete p1;
    // delete p2;
    // delete q1;
    // delete q2;
    return res;
};

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();
    UnlimitedInt *num = p1->mul(p1, p2);
    UnlimitedInt *den = q1->mul(q1, q2);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    // delete p1;
    // delete p2;
    // delete q1;
    // delete q2;
    return res;
};

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q2 = i2->get_q();
    UnlimitedInt *num = p1->mul(p1, q2);
    UnlimitedInt *den = q1->mul(q1, p2);
    UnlimitedRational *res = new UnlimitedRational(num, den);
    // delete p1;
    // delete p2;
    // delete q1;
    // delete q2;
    return res;
};

// int main(){
//     UnlimitedInt* p1 = new UnlimitedInt("56");
//     UnlimitedInt* p2 = new UnlimitedInt("21");
//     // UnlimitedInt* p3 = new UnlimitedInt("168");
//     // UnlimitedInt* p4 = new UnlimitedInt("1");
//     cout<<p1->mul(p1,p2)->to_string()<<endl;
//     //UnlimitedRational* r1 = new UnlimitedRational(p1,p2);
//     // UnlimitedRational* r2 = new UnlimitedRational(p3,p4);
//     //cout<< r1->get_frac_str()<<endl;
//     // cout<< r2->get_frac_str()<<endl;

//     // cout << r1->mul(r1,r1)->get_frac_str()<<endl;
//     // UnlimitedRational* r3 = r1->mul(r1,r1);
//     // cout<<r3->div(r2,r3)->get_frac_str()<<endl;
// }
