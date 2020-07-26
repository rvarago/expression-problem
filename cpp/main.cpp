#include <concepts>
#include <iostream>
#include <sstream>
#include <string>

struct Lit {int value;};

template <typename L, typename R>
struct Add {L left; R right;};

template <typename E>
concept Eval = requires(E e) {
    {eval(e)} -> std::convertible_to<int>;
};

auto eval(Lit const& lit) -> int {
    return lit.value;
}

template <Eval L, Eval R>
auto eval(Add<L, R> const& add) -> int {
    return eval(add.left) + eval(add.right);
}

// Extension: New operation

template <typename P>
concept PPrint = requires(P p) {
    {pprint(p)} -> std::convertible_to<std::string>;
};

auto pprint(Lit const& lit) -> std::string {
    return std::to_string(lit.value);
}

template <PPrint L, PPrint R>
auto pprint(Add<L, R> const& add) -> std::string {
    std::stringstream formatter;
    formatter << "(" << pprint(add.left) << "+" << pprint(add.right) << ")";
    return formatter.str();
}

// Extension: New type

template <typename L, typename R>
struct Mul {L left; R right;};

template <Eval L, Eval R>
auto eval(Mul<L, R> const& mul) -> int {
    return eval(mul.left) * eval(mul.right);
}

template <PPrint L, PPrint R>
auto pprint(Mul<L, R> const& mul) -> std::string {
    std::stringstream formatter;
    formatter << "(" << pprint(mul.left) << "*" << pprint(mul.right) << ")";
    return formatter.str();
}

int main() {
    auto const expr = Mul{Lit{10}, Add{Lit{2}, Lit{3}}};
    std::cout << "C++:" << std::endl;
    std::cout << pprint(expr) << std::endl;
    std::cout << eval(expr) << std::endl;
    return 0;
}