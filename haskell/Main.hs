newtype Lit = Lit Int

data Add l r = Add l r

class Eval e where
  eval :: e -> Int

instance Eval Lit where
  eval (Lit x) = x

instance (Eval l, Eval r) => Eval (Add l r) where
  eval (Add l r) = eval l + eval r

-- Extension: New operation

class PPrint p where
  pprint :: p -> String

instance PPrint Lit where
  pprint (Lit x) = show x

instance (PPrint l, PPrint r) => PPrint (Add l r) where
  pprint (Add l r) = "(" ++ pprint l ++ "+" ++ pprint r ++ ")"

-- Extension: New type

data Mul l r = Mul l r

instance (Eval l, Eval r) => Eval (Mul l r) where
  eval (Mul l r) = eval l * eval r

instance (PPrint l, PPrint r) => PPrint (Mul l r) where
  pprint (Mul l r) = "(" ++ pprint l ++ "*" ++ pprint r ++ ")"

main :: IO ()
main = putStrLn "Haskell: " >> putStrLn (pprint expr) >> print (eval expr)
  where
    expr = Mul (Lit 10) (Add (Lit 2) (Lit 3))