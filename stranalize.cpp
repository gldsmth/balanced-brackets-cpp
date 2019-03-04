#include "stranalize.hpp"
#include <iostream>
#include <functional>

constexpr int BALANCED = -1;

bool is_not_bracket(const char &chr)
{
    static constexpr char brackets[7] = "()[]{}";

    for (int i = 0; i < 7; ++i) if (chr == brackets[i]) return  false;

    return true;
}

struct Bracket
{
    int index;

    bool has_pair = false;

    enum checkpair_result
    {
        MATCH, NOT_MATCHED, NEW_BRACKET
    };

    Bracket(const char &bracket, const int &index)

        : index(index), brpair(getpair(bracket))
    {}

    checkpair_result checkpair(char const &br)
    {
        if ( brpair == WRONGPAIR ) return NOT_MATCHED;

        if ( br == brpair ) {

            has_pair = true;

            return MATCH;
        }
        else {

            if ( getpair(br) == WRONGPAIR ) return NOT_MATCHED;

            else return NEW_BRACKET;
        }
    }

private:
    char brpair;

    static constexpr char WRONGPAIR =  0;

    char getpair(char const &bracket) const
    {
            switch (bracket) {

            case '(': return ')';

            case '[': return ']';

            case '{': return '}';

            default:  return WRONGPAIR;
            }
    }
};

void stranalize::checkstr(const std::string &str)
{
    Stack<char> strstack(str.size());

    for (size_t i = str.size()-1; strstack.size() != str.size(); --i) {

        strstack.push(str[i]);
    }

    Stack<char> strerr(strstack);

    int result = checkstack(strstack);

    if (result == BALANCED) std::cout << "OK. All brackets in string are balanced\n";

    else {

        std::cout << "BAD. Showing string up to the first unclosed bracket.\n";

        for (;strerr.size() != size_t(result); strerr.pop()) std::cout << strerr.top();

        std::cout << '\n';

    }
}

int stranalize::checkstack(Stack<char> &strstack)
{
    std::function<int (bool)> checkstack_;

    checkstack_= [&strstack, &checkstack_] (bool recursion) {

        static int result = BALANCED;

        while ( strstack.empty() != true ) {

            char chr = strstack.top();

            if ( is_not_bracket(chr) ) strstack.pop();

            else {

                Bracket br (chr, static_cast<int> (strstack.size() - 1));

                strstack.pop();

                while ( strstack.empty() != true ) {

                    chr = strstack.top();

                    if ( is_not_bracket(chr) ) strstack.pop();

                    else {

                        auto checkpair_result = br.checkpair(chr);

                        switch (checkpair_result) {

                        case Bracket::MATCH:

                            strstack.pop();

                            if ( recursion ) return BALANCED;

                            break;
                        case Bracket::NOT_MATCHED: return br.index;

                        case Bracket::NEW_BRACKET:

                            result = checkstack_(true);

                            break;
                        }
                        if ( result != BALANCED ) return result;

                        else if ( result == BALANCED && recursion == false && br.has_pair) break;
                    }
                }
                if ( br.has_pair == false ) return br.index;
            }
        }
        return result;
    };

    return checkstack_(false);
}
