#include <memory>
#include <vector>

#include "lex.h"

namespace lang
{

enum ASTType
{
    AST_MAIN,

    AST_VAR,
    AST_VARDEF,
    AST_VARASSIGN,

    AST_SEQUENCE,
    AST_DOFOR,
    AST_DOTHROUGH,

    AST_NUMBER,
    AST_STRING,

    AST_CALL,
    AST_EXTERN,

    AST_IF,
    AST_IFELSE,

    AST_ARRAY,
};

///--- Base AST ---///
class ASTBase
{
    std::unique_ptr<Token> token;
public:
    int type;

    ASTBase(int ast_type, std::unique_ptr<Token> token);
    ASTBase(int ast_type, std::string const& token_value);

    virtual Token* const getToken() const;
    virtual void setToken(std::unique_ptr<Token> new_token);
};
///--- Base AST ---///

///--- Main AST ---///
class MainAST: public ASTBase
{
    std::string program_name;
    std::vector<std::unique_ptr<ASTBase>> body;
public:
    MainAST(std::vector<std::unique_ptr<ASTBase>> body, std::string const& program_name = "main");

    std::string const& getProgramName() const;
    void setProgramName(std::string const& name);

    std::vector<std::unique_ptr<ASTBase>> const& getBody() const;
    void setBody(std::vector<std::unique_ptr<ASTBase>> body);
};
///--- Main AST ---///

///--- Variable AST ---///
class VariableAST: public ASTBase
{
    std::string name;
public:
    VariableAST(std::string const& name);

    std::string const& getName() const;
    void setName(std::string const& new_name);
};
///--- Variable AST ---///

///--- Variable Definition AST ---///
class VariableDefinitionAST: public ASTBase
{
    std::string name;
    std::unique_ptr<ASTBase> value;
public:
    VariableDefinitionAST(std::string const& name, std::unique_ptr<ASTBase> value);

    std::string const& getName() const;
    void setName(std::string const& new_name);
};
///--- Variable Definition AST ---///

///--- Variable Assignment AST ---///
class VariableAssignmentAST: public ASTBase
{
    std::string name;
    std::unique_ptr<ASTBase> value;
public:
    VariableAssignmentAST(std::string const& name, std::unique_ptr<ASTBase> value);

    std::string const& getName() const;
    void setName(std::string const& new_name);
};
///--- Variable Assignment AST ---///

///--- Function Call AST ---///
class FunctionCallAST: public ASTBase
{
    std::string name;
    std::vector<std::unique_ptr<ASTBase>> arguments;
public:
    FunctionCallAST(std::string const& name);
    FunctionCallAST(std::string const& name, std::vector<std::unique_ptr<ASTBase>> arguments);

    std::string const& getName() const;
    void setName(std::string const& new_name);

    std::vector<std::unique_ptr<ASTBase>> const& getArguments() const;
    void setArguments(std::vector<std::unique_ptr<ASTBase>> arguments);
};
///--- Function Call AST ---///

///--- Sequence AST ---///
class SequenceAST: public ASTBase
{
    std::vector<std::unique_ptr<FunctionCallAST>> body;
public:
    SequenceAST();
    SequenceAST(std::vector<std::unique_ptr<FunctionCallAST>> body);

    std::vector<std::unique_ptr<FunctionCallAST>> const& getBody() const;
    void setBody(std::vector<std::unique_ptr<FunctionCallAST>> body);
};
///--- Sequence AST ---///

///--- Do-For AST ---///
class DoForAST: public ASTBase
{
    std::vector<std::unique_ptr<SequenceAST>> sequences;
    std::unique_ptr<ASTBase> for_times_ast;
public:
    DoForAST(std::unique_ptr<ASTBase> for_times_ast);
    DoForAST(std::unique_ptr<ASTBase> for_times_ast, std::vector<std::unique_ptr<SequenceAST>> sequences);

    ASTBase* const getForTimes() const;
    void setForTimes(std::unique_ptr<ASTBase> for_times);

    std::vector<std::unique_ptr<SequenceAST>> const& getSequences() const;
    void setSequences(std::vector<std::unique_ptr<SequenceAST>> sequences);
};
///--- Do-For AST ---///

///--- Do-Through AST ---///
class DoThroughAST: public ASTBase
{
    std::vector<std::unique_ptr<SequenceAST>> sequences;
    std::unique_ptr<ASTBase> through_ast;
public:
    DoThroughAST(std::unique_ptr<ASTBase> through_ast);
    DoThroughAST(std::unique_ptr<ASTBase> through_ast, std::vector<std::unique_ptr<SequenceAST>> sequences);

    ASTBase* const getThrough() const;
    void setThrough(std::unique_ptr<ASTBase> through_ast);

    std::vector<std::unique_ptr<SequenceAST>> const& getSequences() const;
    void setSequences(std::vector<std::unique_ptr<SequenceAST>> sequences);
};
///--- Do-Through AST ---///

///--- Number AST ---///
class NumberAST: public ASTBase
{
    double value;
public:
    NumberAST(double value);

    double const getValue() const;
    void setValue(double value);
};
///--- Number AST ---///

///--- String AST ---///
class StringAST: public ASTBase
{
    std::string value;
public:
    StringAST(std::string const& value);

    std::string const& getValue() const;
    void setValue(std::string const& value);
};
///--- String AST ---///

///--- Extern AST ---///
class ExternAST: public ASTBase
{
    std::string name;
public:
    ExternAST(std::string const& name);

    std::string const& getName() const;
    void setName(std::string const& name);
};
///--- Extern AST ---///
}