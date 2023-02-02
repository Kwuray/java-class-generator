# Help file

USAGE :

  jcvg {CLASSDESC} [OPTIONS] {destpath}

  jcvg -M|-m ==> Main.java


CLASSDESC :

  -c --class

    y|n/[{CLASS-NONACCESS-MODIFIER}]/name

      the y|n mean public or not


OPTIONS :

  \--attr

    [{ATTRIBUTE-ACCESS}]/[{ATTRIBUTE-NONACCESS}]/type/name/{GETTER-ACCESS}/SETTER-ACCESS/y|n

      multiple attributes can be declared. Just seperate them with ":"

      the y|n mean in constructor or not

  \-M

    Add main method ==> abstract class, no constructor

  \-m

    Add main method

  \-s

    Add toString method


CLASS-NONACCESS :

  f ==> final

  a ==> abstract

  n ==> none


ATTRIBUTE-ACCESS :

  \+ ==> public

  \- ==> private

  ~ ==> protected

  n ==> none


ATTRIBUTE-NONACCESS :

  f ==> final
  
  s ==> static

  a ==> abstract

  t ==> transient

  S ==> synchronized

  v ==> volatile

  n ==> none


GETTER-ACCESS-MODIFIER :

  same as ATTRIBUTE-ACCESS


SETTER-ACCESS-MODIFIER :

  same as ATTRIBUTE-ACCESS
