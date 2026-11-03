module Kernel
  A=B=C=D=E=F="defined in Kernel"
end

class Super
  A=B=C=D="defined in superclass"
end

module Included
  A=B=C="defined in included module"
end

#Top level or global constants defined in Objectc
A=B=C=D=E="defined at top-level"

module Enclosing
  A=B="defined in enclosing module"
  class Local < Super
    include Included
    A = "defined locally"
    puts A
    puts B
    puts C
    puts D
    puts E
    puts F
  end
end
