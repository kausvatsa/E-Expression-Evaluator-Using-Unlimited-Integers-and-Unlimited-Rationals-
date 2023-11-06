/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
};

Evaluator::~Evaluator(){
    delete symtable;
};

void Evaluator::parse(vector<string> code)
{

    ExprTreeNode *rt = new ExprTreeNode();
    rt->type = "t";
    rt->id = ":=";
    rt->right = new ExprTreeNode();
    ExprTreeNode *temp = rt->right;
    rt->left = new ExprTreeNode();
    rt->left->id = code[0];
    rt->left->type = "VAR";
    vector<ExprTreeNode *> v;
    v.push_back(rt);
    for (int i = 2; i < code.size(); i++)
    {
        if (code[i] == "(")
        {
            temp->left = new ExprTreeNode();
            v.push_back(temp);
            temp = temp->left;
        }
        else if (code[i] == "+" || code[i] == "-" || code[i] == "*" || code[i] == "/")
        {
            if (code[i] == "+")
            {
                temp->type = "ADD";
                // temp->evaluated_value = temp->left->evaluated_value->add(temp->left->evaluated_value, temp->right->evaluated_value);
            }
            if (code[i] == "-")
            {
                temp->type = "SUB";
                // temp->evaluated_value = temp->left->evaluated_value->sub(temp->left->evaluated_value, temp->right->evaluated_value);
            }
            if (code[i] == "*")
            {
                temp->type = "MUL";
                // temp->evaluated_value = temp->left->evaluated_value->mul(temp->left->evaluated_value, temp->right->evaluated_value);
            }
            if (code[i] == "/")
            {
                temp->type = "DIV";
                // temp->evaluated_value = temp->left->evaluated_value->div(temp->left->evaluated_value, temp->right->evaluated_value);
            }
            temp->id = code[i];
            temp->right = new ExprTreeNode();
            v.push_back(temp);
            temp = temp->right;
        }
        else if (code[i] == ")")
        {
            temp = v[v.size() - 1];
            v.pop_back();
        }
        else
        {
            if (code[i][0] > '9')
            {
                // cout<<"ooii"<<endl;
                temp->type = "VAR";
                temp->id = code[i];
                // // cout<<temp->evaluated_value->get_frac_str()<<endl;
                temp = v[v.size() - 1];
                v.pop_back();
            }
            else
            {
                temp->type = "VAL";
                temp->id = code[i];
                temp->val = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt(1));
                temp->evaluated_value = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt(1));;
                temp = v[v.size() - 1];
                v.pop_back();
            }
        }
    }
    expr_trees.push_back(rt);
};

UnlimitedRational *evaluate(ExprTreeNode *root, SymbolTable *s)
{

    UnlimitedRational *one = new UnlimitedRational(new UnlimitedInt(1), new UnlimitedInt(1));
    if(root==nullptr){
        return new UnlimitedRational(new UnlimitedInt(0),new UnlimitedInt(1));
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        if (root->type == "VAR")
        {

            root->evaluated_value= new UnlimitedRational(s->search(root->id)->get_p(), s->search(root->id)->get_q());
        }
        return new UnlimitedRational(root->evaluated_value->get_p(),root->evaluated_value->get_q());
    }
    else
    {
        if (root->type == "ADD")
        {
            root->evaluated_value = new UnlimitedRational(one->add(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->add(evaluate(root->left, s), evaluate(root->right, s))->get_q());
            return new UnlimitedRational(one->add(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->add(evaluate(root->left, s), evaluate(root->right, s))->get_q());
        }
        if (root->type == "SUB")
        {
            root->evaluated_value = new UnlimitedRational(one->sub(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->sub(evaluate(root->left, s), evaluate(root->right, s))->get_q());
            return new UnlimitedRational(one->sub(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->sub(evaluate(root->left, s), evaluate(root->right, s))->get_q());;
        }
        if (root->type == "MUL")
        {
            root->evaluated_value = new UnlimitedRational(one->mul(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->mul(evaluate(root->left, s), evaluate(root->right, s))->get_q());
            return new UnlimitedRational(one->mul(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->mul(evaluate(root->left, s), evaluate(root->right, s))->get_q());;
        }
        if (root->type == "DIV")
        {
            root->evaluated_value = new UnlimitedRational(one->div(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->div(evaluate(root->left, s), evaluate(root->right, s))->get_q());
            return new UnlimitedRational(one->div(evaluate(root->left, s), evaluate(root->right, s))->get_p(), one->div(evaluate(root->left, s), evaluate(root->right, s))->get_q());;
        }
    }
};

void Evaluator::eval()
{
    ExprTreeNode *r = expr_trees[expr_trees.size() - 1];
    //r->evaluated_value = new UnlimitedRational(evaluate(r->right,symtable)->get_p(),evaluate(r->right,symtable)->get_q());
    r->left->evaluated_value = new UnlimitedRational(evaluate(r->right,symtable)->get_p(),evaluate(r->right,symtable)->get_q());
    symtable->insert(r->left->id, r->left->evaluated_value);
};

// void printInorder(ExprTreeNode *root)
// {
//     if (root == nullptr)
//         return;

//     // First recur on left subtree
//     // cout << "(";
//     printInorder(root->left);

//     // Now deal with the root
//     cout << root->evaluated_value->get_frac_str() << " ";

//     // Then recur on right subtree
//     printInorder(root->right);
//     // cout << ")";
// };

// void printInorder1(SymEntry *root)
// {
//     if (root == nullptr)
//         return;

//     // First recur on left subtree

//     printInorder1(root->left);

//     // Now deal with the root
//     cout << root->val->get_frac_str() << " ";

//     // Then recur on right subtree
//     printInorder1(root->right);
// };



// int main()
// {
//     vector<string> v1 = {"pow1", ":=", "13"};
//     vector<string> v2 = {"pow2", ":=", "(", "(", "2", "*", "42", ")", "/", "(", "pow1", "*", "pow1", ")", ")"};
//     vector<string> v3 = {"pow3", ":=", "(", "(", "3", "*", "42", ")", "/", "(", "pow2", "*", "pow2", ")", ")"};
//     vector<string> v4 = {"pow4", ":=", "(", "(", "4", "*", "42", ")", "/", "(", "pow3", "*", "pow3", ")", ")"};
//     vector<string> v5 = {"pow5", ":=", "(", "(", "5", "*", "42", ")", "/", "(", "pow4", "*", "pow4", ")", ")"};

//     Evaluator *e = new Evaluator();

//     e->parse(v1);
//     e->eval();
//     // cout<<e->expr_trees[0]->left->evaluated_value->get_frac_str()<<endl;
//     //<<e->symtable->search("a")->get_frac_str()<<endl;
//     // cout << e->expr_trees[0]->left->evaluated_value->get_frac_str() << endl;
//     // printInorder(e->expr_trees[0]);
//     // cout << endl;
//     e->parse(v2);
//     e->eval();
//     // cout << e->expr_trees[1]->left->evaluated_value->get_frac_str() << endl;
//     // cout << "aara aara: ";
//     // printInorder(e->expr_trees[1]);
//     // cout << endl;
//     // printInorder(e->expr_trees[0]);
//     // cout<<e->symtable->search("a")->get_frac_str()<<endl;
//     e->parse(v3);
//     e->eval();
//     // cout << e->expr_trees[2]->left->evaluated_value->get_frac_str() << endl;
//     // printInorder(e->expr_trees[2]);

//     // cout << endl;
//     // printInorder(e->expr_trees[0]_root());
//     // cout<<e->symtable->search("a")->get_frac_str()<<endl;

//     // cout<<e->expr_trees[2]->left->evaluated_value->get_frac_str()<<endl;
//     e->parse(v4);
//     e->eval();
//     // cout << " ooii" << endl;
//     // e->symtable->insert("pow4",new UnlimitedRational(new UnlimitedInt("815730721"),new UnlimitedInt(3136)));
//     // printInorder1(e->symtable->get_root());
//     cout << e->expr_trees[3]->right->evaluated_value->get_frac_str() << endl;
//     // printInorder(e->expr_trees[3]);
//     //cout << endl;
//     e->parse(v5);
//     e->eval();
//     cout << e->expr_trees[4]->left->evaluated_value->get_frac_str() << endl;
//     // printInorder1(e->symtable->get_root());
//     // cout << endl;
//     // printInorder(e->expr_trees[4]);
//     // cout << endl;
//     // printInorder1(e->symtable->get_root());
//     cout<<endl<<"completed!"<<endl;
// }