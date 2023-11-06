/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode()
{
    type = "";
    id = "";
    val = nullptr;
    evaluated_value = nullptr;
    left = nullptr;
    right = nullptr;
};

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v){};

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v){};

ExprTreeNode::~ExprTreeNode()
{
    if (evaluated_value != nullptr && val != nullptr)
    {
        delete evaluated_value;
        delete val;
    }
    evaluated_value = nullptr;
    val = nullptr;
};