struct Lit(i32);
struct Add<L, R>(L, R);

trait Eval {
    fn eval(&self) -> i32;
}

impl Eval for Lit {
    fn eval(&self) -> i32 {
        self.0
    }
}

impl <L, R> Eval for Add<L, R>
where L: Eval,
      R: Eval {
    fn eval(&self) -> i32 {
        self.0.eval() + self.1.eval()
    }
}

// Extension: New operation

trait PPrint {
    fn pprint(&self) -> String;
}

impl PPrint for Lit {
    fn pprint(&self) -> String {
        self.0.to_string()
    }
}

impl <L, R> PPrint for Add<L, R>
where L: PPrint,
      R: PPrint {
    fn pprint(&self) -> String {
        format!("({}+{})", self.0.pprint(), self.1.pprint())
    }
}

// Extension: New type

struct Mul<L, R>(L, R);

impl <L, R> Eval for Mul<L, R>
where L: Eval,
      R: Eval {
    fn eval(&self) -> i32 {
        self.0.eval() * self.1.eval()
    }
}

impl <L, R> PPrint for Mul<L, R>
where L: PPrint,
      R: PPrint {
    fn pprint(&self) -> String {
        format!("({}*{})", self.0.pprint(), self.1.pprint())
    }
}

fn main() {
    println!("Rust:");

    let expr = Mul(Lit(10), Add(Lit(2), Lit(3)));

    println!("{}", expr.pprint());
    println!("{}", expr.eval());
}