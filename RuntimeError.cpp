#include "TokenType.h"

using namespace std;
class RuntimeError: runtime_error {
public:
        const Token token;
        string message;
        RuntimeError(Token token, string message): runtime_error(message), message(message), token(token){}
};

