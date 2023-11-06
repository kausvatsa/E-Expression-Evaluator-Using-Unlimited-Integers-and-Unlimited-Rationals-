/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
};
SymbolTable::~SymbolTable()
{

    //delete root;

};

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    SymbolTable *temp = new SymbolTable();
    if (root == nullptr)
    {
        root = new SymEntry(k, v);
        size++;
    }
    else if (root->key > k)
    {
        if (root->left == nullptr)
        {
            root->left = new SymEntry(k, v);
            size++;
        }
        else
        {

            temp->root = root->left;
            temp->insert(k, v);
            size++;
            // delete temp;
        }
    }
    else if (root->key < k)
    {
        if (root->right == nullptr)
        {
            root->right = new SymEntry(k, v);
            size++;
        }
        else
        {
            temp->root = root->right;
            temp->insert(k, v);
            size++;
            // delete temp;
        }
    }
};

void SymbolTable::remove(string k)
{
    if (root->left == nullptr && root->right == nullptr && root->key == k)
    {
        root = nullptr;
        root->key = "";
        root->val = nullptr;
        size--;
    }
    else if (root->left == nullptr && root->right != nullptr && root->key == k)
    {
        SymEntry *temp1 = new SymEntry();
        temp1 = root->right;
        root->right = root;
        root = temp1;
        SymbolTable *temp;
        temp->root = root->right;
        temp->remove(k);
    }
    else if (root->right == nullptr && root->left != nullptr && root->key == k)
    {
        SymEntry *temp1 = new SymEntry();
        temp1 = root->left;
        root->left = root;
        root = temp1;
        SymbolTable *temp;
        temp->root = root->left;
        temp->remove(k);
    }
    else if (root->key == k)
    {
        SymEntry *node = root->right;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        SymEntry *temp1;
        temp1 = node;
        node = root;
        root = temp1;
        SymbolTable *temp;
        temp->root = node;
        temp->remove(k);
    }
    else if (k < root->key)
    {
        SymbolTable *temp;
        temp->root = root->left;
        temp->remove(k);
    }
    else if (k > root->key)
    {
        SymbolTable *temp;
        temp->root = root->right;
        temp->remove(k);
    }
};

UnlimitedRational *SymbolTable::search(string k)
{
    SymbolTable *temp = new SymbolTable();
    if (root->key == k)
    {
        return root->val;
    }
    else if (root->key > k)
    {
        temp->root = root->left;
        return temp->search(k);
    }
    else if (root->key < k)
    {

        temp->root = root->right;
        return temp->search(k);
    }
    return 0;
};

int SymbolTable::get_size()
{
    return size;
};

SymEntry *SymbolTable::get_root()
{
    return root;
};




// int main()
// {
//     UnlimitedInt *one = new UnlimitedInt(1);
//     UnlimitedRational *v = new UnlimitedRational(one, one);
//     UnlimitedRational *v1 = new UnlimitedRational(new UnlimitedInt(5), one);
//     UnlimitedRational *v2 = new UnlimitedRational(new UnlimitedInt(10), new UnlimitedInt(5));
//     SymbolTable *s = new SymbolTable();
//     SymEntry *r = new SymEntry("x", v);
//     s->insert("x", v);
//     cout<<s->get_root()->key<<endl;
//     s->insert("y", v1);
//     cout<<s->search("y")->get_frac_str()<<endl;
//     cout<<s->get_root()->key<<endl;
//     s->insert("z",v2);
//     cout << s->get_size() << endl;
//     cout<<s->search("x")->get_frac_str()<<endl;

//     cout<<s->search("z")->get_frac_str()<<endl;
//     cout<<s->search("y")->get_frac_str()<<" is x finally"<<endl;
//     cout<<s->get_size()<<endl;
// }