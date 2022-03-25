# include <iostream>
# include <stdlib.h> // exit( 0 )
# include <string.h> // strcpy, strlen
# include <vector>   // vector
# include <string>

using namespace std;

struct Variable {
  string type;
  string name;
  string arraysize;
};

struct Function {
  string type;
  string name;
  vector<Variable> fparameter;
  vector<string> data;
};

class Exception {
  public:
  string mMsg ;
  Exception() {  }

  Exception( string x ) {
    mMsg = x ;
  } // Exception()

} ; // class Expception

class Exception1 : public Exception {
  public:
  Exception1( string x ) {
    mMsg = x ;
  } // Exception1()
} ; // class Exception1

class Exception2 : public Exception {
  public:
  Exception2( string x ) {
    mMsg = x ;
  } // Exception2()
} ; // class Exception2

class Exception3 : public Exception {
  public:
  Exception3( string x ) {
    mMsg = x ;
  } // Exception3()
} ; // class Exception3

class Exception4 : public Exception {
  public:
  Exception4( ) {
    ;
  } // Exception4()
}; // class Exception4

static vector<Function> ufunction; // declarator function
static vector<Variable> uparameter;       // declarator paraeter
static Function ut_function;    // declarator temp
static Variable ut_variable;
static string ucode;

static int uLine;
static int uBracket ;
static bool uisfunction;
static bool uIn_if;
static bool uIn_while;
static string ustate;

string GetToken( ) ;
string PeekToken( ) ;
void Skip_comment( ) ;

void User_input( ) ;
void Definition( ) ;
string Type_specifier( ) ;
void Rest_of_declarators( ) ;
void Function_definition_without_ID( ) ;
void Formal_parameter_list( ) ;
void Compound_statement( ) ;
void Declaration( ) ;
void Statement( ) ;
void Notout_Statement( ) ;
void Expression( ) ;
void Basic_expression( ) ;
void Rest_of_Identifier_started_basic_exp( ) ;
void Rest_of_PPMM_Identifier_started_basic_exp( ) ;
bool Sign( string peek ) ;
void Actual_parameter_list( ) ;
bool Assignment_operator( string token ) ;
void Romce_and_romloe( ) ;
void Rest_of_maybe_logical_OR_exp( ) ;
void Maybe_logical_AND_exp( ) ;
void Rest_of_maybe_logical_AND_exp( ) ;
void Maybe_bit_OR_exp( ) ;
void Rest_of_maybe_bit_OR_exp( ) ;
void Maybe_bit_ex_OR_exp( ) ;
void Rest_of_maybe_bit_ex_OR_exp( ) ;
void Maybe_bit_AND_exp( ) ;
void Rest_of_maybe_bit_AND_exp( ) ;
void Maybe_equality_exp( ) ;
void Rest_of_maybe_equality_exp( ) ;
void Maybe_relational_exp( ) ;
void Rest_of_maybe_relational_exp( ) ;
void Maybe_shift_exp( ) ;
void Rest_of_maybe_shift_exp( ) ;
void Maybe_additive_exp( ) ;
void Rest_of_maybe_additive_exp( ) ;
void Maybe_mult_exp( ) ;
void Rest_of_maybe_mult_exp( ) ;
void Unary_exp( ) ;
void Signed_unary_exp( ) ;
void Unsigned_unary_exp( ) ;

bool SearchID( string token ) ;
bool Search_FID( string token ) ;
bool Is_ID( string token ) ;
bool Is_Constant( string token ) ;
void ListAllVariables( ) ;
void ListVariable( ) ;
void ListAllFunctions( ) ;
void ListFunction( ) ;
void Error( string token ) ;
bool Know( string id ) ;

int main()
{
  char trash[256] ;
  string uTestNum = "";
  cin >> uTestNum ; // uTestNum
  cin.getline( trash, 256 );
  cout << "Our-C running ..." << endl;
  while ( true ) {
    try {
      ustate = "";
      ucode = "";
      uisfunction = false;
      uIn_if = false;
      uIn_while = false;
      uBracket = 0;
      cout << "> " ;
      uLine = 1;
      User_input( );
    } // try
    catch ( Exception1 * e ) {
      cout << "Line " << uLine << " : unrecognized token with first char : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception2 * e ) {
      cout << "Line " << uLine << " : unexpected token : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception3 * e ) {
      cout << "Line " << uLine << " : undefined identifier : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception4 * e ) {
      cout << "Line " << uLine << " : Error" << endl;
      cin.getline( trash, 256 );
    } // catch
  } // while()

  return 0 ;
} // main()


string GetToken( ) {
  string name = "";
  char trash[ 256 ];
  char c = '\0', peek = cin.peek();
  while ( true ) {
    if ( ( peek >= 'A' && peek <= 'Z' ) || ( peek >= 'a' && peek <= 'z' ) ) {
      // IDENT
      c = cin.get();
      name = name + c;
      peek = cin.peek();
      while ( ( peek >= 'A' && peek <= 'Z' ) || ( peek >= 'a' && peek <= 'z' )
              || ( peek >= '0' && peek <= '9' ) || peek == '_' ) {
        c = cin.get();
        name = name + c;
        peek = cin.peek();
      } // while()

      return name;
    } // if()
    else if ( ( peek >= '0' && peek <= '9' ) || peek == '.' ) {
      bool dot = false;
      c = cin.get();
      if ( c == '.' ) dot = true;
      name = name + c;
      peek = cin.peek();
      if ( dot ) {
        while ( peek >= '0' && peek <= '9' ) {
          c = cin.get();
          name = name + c;
          peek = cin.peek();
        }  // while()
      } // if
      else {
        while ( ( peek >= '0' && peek <= '9' ) || peek == '.' ) {
          c = cin.get();
          if ( c == '.' ) dot = true;
          name = name + c;
          peek = cin.peek();
          if ( dot && peek == '.' ) return name ;
        }  // while()
      } // else

      return name;
    } // else if()
    else if ( peek == '*' || peek == '%' ) {
      // "*=", "%="
      // "/=" 與註解一起處理
      c = cin.get();
      name = name + c ;
      if ( peek == '=' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
    } // else if
    else if ( peek == '+' ) { // "+", "+=", "++"
      c = cin.get();
      name = name + c ;
      peek = cin.peek();
      if ( peek == '=' || peek == '+' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
    } // else if
    else if ( peek == '-' ) { // "-", "-=", "--"
      c = cin.get();
      name = name + c ;
      peek = cin.peek();
      if ( peek == '=' || peek == '-' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
    } // else if
    else if ( peek == '<' ) { // "<", "<=", "<<"
      c = cin.get();
      name = name + c ;
      peek = cin.peek();
      if ( peek == '=' || peek == '<' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
    } // else if
    else if ( peek == '>' ) { // ">", ">=", ">>"
      c = cin.get();
      name = name + c;
      peek = cin.peek();
      if ( peek == '=' || peek == '>' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
    } // else if
    else if ( peek == '=' || peek == '!' ) { // "=", "==", "!="
      c = cin.get();
      name = name + c;
      peek = cin.peek();
      if ( peek == '=' ) {
        c = cin.get();
        name = name + c ;
      } // if

      return name ;
    } // else if
    else if ( peek == '&' ) { // "&", "&&"
      c = cin.get();
      name = name + c;
      peek = cin.peek();
      if ( peek == '&' ) {
        c = cin.get();
        name = name + c ;
      } // if

      return name ;
    } // else if
    else if ( peek == '|' ) { // "|", "||"
      c = cin.get();
      name = name + c;
      peek = cin.peek();
      if ( peek == '|' ) {
        c = cin.get();
        name = name + c ;
      } // if

      return name ;
    } // else if
    else if ( peek == ' ' || peek == '\n' || peek == '/' ) {
      c = cin.get();
      if ( c == '\n' ) uLine++;
      else if ( c == '/' ) {
        char c2 = cin.peek( );
        if ( c2 == '/' ) {
          cin.getline( trash, 256 ); // is comment
          uLine++;
        } // if
        else if ( c2 == '=' ) {
          c2 = cin.get( );
          name = name + c + c2;
          return name ;
        } // else if
        else {
          name = name + c;
          return name ;
        } // else
      } // else if

      peek = cin.peek();
    } // else if
    else if ( peek == '"' ) {            //  "....."
      c = cin.get();
      name = name + c;
      c = cin.peek();
      while ( c != '"' ) {
        c = cin.get();
        name = name + c;
        c = cin.peek();
      } // while

      c = cin.get();
      name = name + c;
      return name;
    } // else if
    else {
      c = cin.get();
      name = name + c;
      return name ;
    } // else
  } // while()

  return name ;
} // GetToken()

string PeekToken( ) {
  char store[50];
  string s_peek = GetToken();
  strcpy( store, s_peek.c_str( ) );
  for ( int i = s_peek.size( ) -1 ; i >= 0 ; i-- )
    cin.putback( store[ i ] ) ;

  return s_peek;
} // PeekToken()

void Skip_comment( ) {
  char a = cin.get( );
  while ( a == ' ' ) a = cin.get( );
  if ( a == '/' ) {
    char b = cin.peek( );
    if ( b == '/' ) {
      char trash[ 256 ];
      cin.getline( trash, 256 );
      uLine++;
    } // if
  } // if
  else if ( a == '\n' ) uLine++;
  else cin.putback( a );
} // Skip_comment()

void User_input( ) {
  // : ( definition | statement ) { definition | statement }

  string peek = PeekToken();
  if ( peek == "void" || peek == "int" || peek == "char"
       || peek == "float" || peek == "string" || peek == "bool" )
    Definition();
  else
    Statement();
} // User_input()

void Definition() {
  // :           VOID Identifier function_definition_without_ID
  // | type_specifier Identifier function_definition_or_declarators

  string type = "", name = "";
  string peek = PeekToken();
  if ( peek == "void" ) {
    ut_function.type = GetToken();                // "void"
    ucode = ucode + ut_function.type ;
    ut_function.name = GetToken();                            // "ID"
    if ( !Is_ID( ut_function.name ) ) Error( ut_function.name );
    ucode = ucode + " " + ut_function.name ;
    Function_definition_without_ID();
  } // if
  else {
    type = Type_specifier();          // "int", "char", "float", "string", "bool"
    ucode = ucode + type ;
    name = GetToken();                // "ID"
    if ( !Is_ID( name ) ) Error( name );
    ucode = ucode + " " + name ;
    peek = PeekToken();
    if ( peek == "(" ) {  // this is function definition
      ut_function.type = type;
      ut_function.name = name;
      Function_definition_without_ID();
    } // if
    else {                 // variable declaration
      ut_variable.type = type;
      ut_variable.name = name;
      Rest_of_declarators();
    } // else
  } // else
} // Definition()

string Type_specifier() {
  // : INT | CHAR | FLOAT | STRING | BOOL
  string type = GetToken();
  if ( type == "int" || type == "float" || type == "char" || type == "bool" || type == "string" )
    return type;
  else Error( type );

  return type;
} // Type_specifier()

void Rest_of_declarators( ) {
  // : [ '[' Constant ']' ]
  //  { ',' Identifier [ '[' Constant ']' ] } ';'

  vector<Variable> nsurevariable;
  Variable temp_variable;
  string peek = PeekToken();
  string token = "";

  temp_variable.type = ut_variable.type;
  temp_variable.name = ut_variable.name;
  temp_variable.arraysize = "" ;
  if ( peek == "[" ) {
    token = GetToken();                    // "["
    ucode = ucode + token ;
    token = GetToken();                    //  Constant
    if ( !Is_Constant( token ) ) Error( token );
    ucode = ucode + " " + token ;
    temp_variable.type = ut_variable.type;
    temp_variable.name = ut_variable.name;
    temp_variable.arraysize = token ;
    token = GetToken();                    // "]"
    if ( token != "]" ) Error( token );
    ucode = ucode + " " + token ;
  } // if()

  nsurevariable.push_back( temp_variable );

  string name = "";
  peek = PeekToken();
  while ( peek == "," ) {
    token = GetToken();                     // ","
    ucode = ucode + token ;
    name = GetToken();
    if ( !Is_ID( name ) ) Error( token );   //  ID
    ucode = ucode + " " + name ;

    peek = PeekToken() ;
    if ( peek == "[" ) {
      token = GetToken();                   // "["
      ucode = ucode + token;
      token = GetToken();                   //  Constant
      if ( !Is_Constant( token ) ) Error( token );
      else ucode = ucode + " " + token ;
      temp_variable.type = ut_variable.type;
      temp_variable.name = name;
      temp_variable.arraysize = token ;
      token = GetToken();                   // "]"
      if ( token != "]" ) Error( token );
      else ucode = ucode + " " + token;
    } // if
    else {
      temp_variable.type = ut_variable.type;
      temp_variable.name = name;
      temp_variable.arraysize = "" ;
    } // else

    nsurevariable.push_back( temp_variable );
    peek = PeekToken();
  } // while()

  token = GetToken();                       // ";"

  if ( token != ";" ) Error( token );
  else ucode = ucode + " " + token ;

  bool add_finish = false;
  if ( uisfunction ) {     // declaration 出
    for ( int i = 0 ; i < nsurevariable.size() ; i++ )  {
      for ( int j = 0 ; j < ut_function.fparameter.size() ; j++ ) {
        if ( nsurevariable[i].name == ut_function.fparameter[j].name ) {
          uparameter[j].arraysize = nsurevariable[i].arraysize;
          uparameter[j].type = nsurevariable[i].type;
          add_finish = true;

          j = uparameter.size();
        } // if
      } // for

      if ( !add_finish ) ut_function.fparameter.push_back( nsurevariable[i] );
    } // for

    ut_function.data.push_back( ucode );
    ucode = "";
  } // if
  else {                   // declaration ( not in function )
    for ( int i = 0 ; i < nsurevariable.size() ; i++ ) {
      for ( int j = 0 ; j < uparameter.size() ; j++ ) {
        if ( nsurevariable[i].name == uparameter[j].name ) {
          uparameter[j].arraysize = nsurevariable[i].arraysize;
          uparameter[j].type = nsurevariable[i].type;
          add_finish = true;

          // due to find out so let this for finish
          cout << "New definition of " << uparameter[j].name << " entered ..." << endl;
          j = uparameter.size();
        } // if
      } // for

      if ( !add_finish ) {
        uparameter.push_back( nsurevariable[i] );
        cout << "Definition of " << uparameter[ uparameter.size() - 1].name << " entered ..." << endl;
      } // if
    } // for
  } // else

  Skip_comment( );
  nsurevariable.clear();
  temp_variable.type = "";
  temp_variable.name = "";
  temp_variable.arraysize = "";
} // Rest_of_declarators()

void Function_definition_without_ID( ) {
  // : '(' [ VOID | formal_parameter_list ] ')' compound_statement
  string peek = "";
  string token = GetToken();             // "("
  if ( token == "(" ) {
    uisfunction = true;
    ucode = ucode + token ;
    peek = PeekToken();
    if ( peek == "void" ) {              // "void"
      token = GetToken();  // "void"
      ucode = ucode + " " + token ;
    } // if
    else if ( peek == "int" || peek == "char" || peek == "float"
              || peek == "string" || peek == "bool" )
      Formal_parameter_list();

    token = GetToken();                   // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token;

    Compound_statement();
  } // if()
  else Error( token );
} // Function_definition_without_ID()

void Formal_parameter_list() {   // function 的參數
  // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ]
  // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
  Variable temp_variable;
  temp_variable.type = Type_specifier();        // type
  ucode = ucode + " " + temp_variable.type + " ";
  string peek = PeekToken();
  string token = "";

  if ( peek == "&" ) {
    token = GetToken();                         // "&"
    ucode = ucode + token;
  } // if

  token =  GetToken();                          // ID
  if ( !Is_ID( token ) ) Error( token );
  else {
    temp_variable.name = token;
    ucode = ucode + temp_variable.name;
  } // else

  peek = PeekToken();
  if ( peek == "[" ) {
    token = GetToken();                         // "["
    ucode = ucode + token;
    token = GetToken();                         // Constant
    if ( !Is_Constant( token ) ) Error( token );
    else {
      temp_variable.arraysize = token ;
      ucode = ucode + " " + token ;
    } // else

    token = GetToken();                         // "]"
    if ( token != "]" ) Error( token );
    else ucode = ucode + " " + token;
    peek = PeekToken();
  } // if()

  ut_function.fparameter.push_back( temp_variable );

  while ( peek == "," ) {
    token = GetToken();                         // ","
    ucode = ucode + token ;
    temp_variable.type = Type_specifier();                    // type
    ucode = ucode + " " + temp_variable.type ;
    peek = PeekToken();
    if ( peek == "&" ) {
      token = GetToken();      // "&"
      ucode = ucode + " " + token;
    } // if

    token = GetToken();                         // ID
    if ( !Is_ID( token ) ) Error( token );
    else {
      temp_variable.name = token;
      ucode = ucode + temp_variable.name ;
    } // else

    peek = PeekToken();
    if ( peek == "[" ) {
      token = GetToken();                        // "["
      ucode = ucode + token ;
      token = GetToken();                        // Constant
      if ( !Is_Constant( token ) ) Error( token );
      else {
        temp_variable.arraysize = token ;
        ucode = ucode + " " + token;
      } // else

      token = GetToken();                        // "]"
      if ( token != "]" ) Error( token );
      else ucode = ucode + " " + token ;
      peek = PeekToken();
    } // if

    ut_function.fparameter.push_back( temp_variable );
  } // while()

} // Formal_parameter_list()

void Compound_statement() {
  // : '{' { declaration | statement } '}'
  string token = GetToken();
  if ( token != "{" ) Error( token );            // "{"
  else ucode = ucode + " " + token ;

  uBracket++;
  uisfunction = true;
  if ( uisfunction ) ut_function.data.push_back( ucode );
  ucode = "";

  string peek = PeekToken();

  // if peek != "}"   =>  "{" ... "}" have something
  while ( peek != "}" ) {
    if ( peek == "int" || peek == "float" || peek == "char" || peek == "string" || peek == "bool" )
      Declaration();
    else Statement();

    peek = PeekToken();
  } // while()

  token = GetToken();
  if ( token != "}" ) Error( token );
  else {
    uBracket--;
    ucode = ucode + token ;
    ut_function.data.push_back( ucode );
    ucode = "";

    if ( uIn_if ) uIn_if = false;
    else if ( uIn_while ) uIn_while = false;
    else if ( uBracket == 0 ) {
      if ( uisfunction && !uIn_if && !uIn_while ) {
        bool addfinish = false;
        for ( int i = 0 ; i < ufunction.size() ; i++ ) {
          if ( ut_function.name == ufunction[i].name ) {
            ufunction[i].name = ut_function.name;
            ufunction[i].type = ut_function.type;
            ufunction[i].fparameter = ut_function.fparameter;
            ufunction[i].data = ut_function.data;
            cout << "New definition of " << ut_function.name << "() entered ..." << endl;
            addfinish = true;
          } // if
        } // for

        if ( ut_function.name == "" )
          cout << "Statement executed ..." << endl;
        else {
          if ( !addfinish ) {
            ufunction.push_back( ut_function );
            cout << "Definition of " << ut_function.name << "() entered ..." << endl;
          } // if
        } // else

        ut_variable.name = "";
        ut_variable.type = "";
        ut_variable.arraysize = "";
        ut_function.name = "";
        ut_function.type = "";
        ut_function.data.clear();
        ut_function.fparameter.clear();
        ucode = "";
      } // if
      else cout << "Statement executed ..." << endl;
    } // else if
  } // else

  Skip_comment();
} // Compound_statement()

void Declaration() {
  // : type_specifier Identifier rest_of_declarators
  ut_variable.type = Type_specifier();              // type
  ucode = ucode + ut_variable.type;

  ut_variable.name = GetToken();                    // ID
  if ( !Is_ID( ut_variable.name ) ) Error( ut_variable.name );
  ucode = ucode + " " + ut_variable.name;
  Rest_of_declarators();
} // Declaration()

void Statement() {
  // : ';'     // the null statement
  //  | expression ';'   // expression here should not be empty
  //  | RETURN [ expression ] ';'
  //  | compound_statement
  //  | IF '(' expression ')' statement [ ELSE statement ]
  //  | WHILE '(' expression ')' statement
  //  | DO statement WHILE '(' expression ')' ';'

  string peek = PeekToken();
  string token = "";
  if ( peek == ";" ) {
    token = GetToken();
    ucode = ucode + " " + token ;
    if ( uisfunction ) ut_function.data.push_back( ucode );
    ucode = "";
    Skip_comment( );

    if ( !uisfunction && !uIn_if && !uIn_while )
      cout << "Statement executed ..." << endl;
    return ;
  } // if
  else if ( peek == "return" ) {
    token = GetToken();                         // return
    ucode = ucode + token ;
    peek = PeekToken();

    if ( peek != ";" ) Expression();

    token = GetToken();                         // ";"
    if ( token != ";" ) Error( token );

    ucode = ucode + " " + token ;
    if ( uisfunction ) ut_function.data.push_back( ucode );
    ucode = "";
  } // else if
  else if ( peek == "{" ) Compound_statement();
  else if ( peek == "if" ) {
    uIn_if = true;
    token = GetToken();                         // if
    ucode = ucode + token;

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    ucode = ucode + " " + token ;

    Expression( );

    token = GetToken();
    if ( token != ")" ) Error( token );         // ")"
    ucode = ucode + " " + token ;

    Statement();

    peek = PeekToken();
    if ( peek == "else" ) {
      token = GetToken();                       // else
      ucode = ucode + " " + token ;
      Statement();
    } // if

    if ( !uisfunction && uIn_if && !uIn_while )
      cout << "Statement executed ..." << endl;
  } // else if
  else if ( peek == "while" ) {
    uIn_while = true;
    token = GetToken();                         // while
    ucode = ucode + token ;

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    ucode = ucode + " " + token ;

    Expression();

    token = GetToken();
    if ( token != ")" ) Error( token );         // ")"
    ucode = ucode + " " + token ;
    Statement();

    if ( !uisfunction && !uIn_if && uIn_while )
      cout << "Statement executed ..." << endl;
  } // else if
  else if ( peek == "do" ) {
    token = GetToken();                         // do
    ucode = ucode + token ;

    Statement();

    token = GetToken();                         // while
    if ( token != "while" ) Error( token );
    ucode = ucode + " " + token ;

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    ucode = ucode + " " + token ;

    Expression();

    token = GetToken();                         // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token ;

    token = GetToken();                         // ";"
    if ( token != ";" ) Error( token );
    ucode = ucode + " " + token ;
    if ( uisfunction ) ut_function.data.push_back( ucode );
    ucode = "";

    if ( !uisfunction && !uIn_if && !uIn_while )
      cout << "Statement executed ..." << endl;
  } // else if
  else {
    if ( Is_ID( peek ) ) {
      if ( peek == "cin" ) {                       // deal with "cin"
        token = GetToken();
        ucode = ucode + token ;

        token = GetToken();                       // ">>"
        if ( token != ">>" ) Error( token );
        ucode = ucode + " " + token ;

        token = GetToken();                       // ID
        if ( !uisfunction && !SearchID( token ) ) throw new Exception3( token );
        else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
        ucode = ucode + " " + token ;

        peek = PeekToken();
        if ( peek == "[" ) {
          token = GetToken();                    // "["
          ucode = ucode + token ;

          token = GetToken();                    //  Constant or ID
          if ( !Is_Constant( token ) && !Is_ID( token ) ) Error( token );
          else {
            if ( !uisfunction && !SearchID( token ) )  throw new Exception3( token );
            else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
          } // else

          ucode = ucode + " " + token ;

          token = GetToken();                    // "]"
          if ( token != "]" ) Error( token );
          ucode = ucode + " " + token ;
        } // if()
      } // if
      else if ( peek == "cout" ) {                 // deal with "cout"
        token = GetToken();                       // "cout"
        ucode = ucode + token ;

        token = GetToken();                       // "<<"
        if ( token != "<<" ) Error( token );
        ucode = ucode + token ;

        Expression();
      } // else if
    } // if
    else
      Expression();


    token = GetToken();                         // ";"
    if ( token != ";" ) Error( token );
    if ( ucode == "" ) ucode = ucode + token ;
    else ucode = ucode + " " + token ;
    if ( uisfunction ) ut_function.data.push_back( ucode );
    ucode = "";

    Skip_comment( );
    if ( ustate == "Done" ) {
      cout << "Our-C exited ..." << endl;
      // system( "pause" ) ;
      exit( 0 ) ;
    } // if
    else if ( ustate == "ListAllVariables" ) ListAllVariables( );
    else if ( ustate == "ListAllFunctions" ) ListAllFunctions( );
    else if ( ustate == "ListVariable" ) ListVariable( );
    else if ( ustate == "ListFunction" ) ListFunction( );

    if ( !uisfunction && !uIn_if && !uIn_while )
      cout << "Statement executed ..." << endl;
    Skip_comment( );
  } // else
  /*
  else {
    token = GetToken();
    Error( token );
  } // else
  */
} // Statement()

void Expression() {
  // basic_expression { ',' basic_expression }
  Basic_expression();
  string peek = PeekToken();
  while ( peek == "," ) {
    string token = GetToken();                  // ","
    ucode = ucode + token ;
    Basic_expression();
    peek = PeekToken();
  } // while
} // Expression()

void Basic_expression() {
  // : Identifier rest_of_Identifier_started_basic_exp
  //  | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
  //  | sign { sign } signed_unary_exp romce_and_romloe
  //  | ( Constant | '(' expression ')' ) romce_and_romloe

  string peek = PeekToken();
  cout << PeekToken() << endl;
  string token = "";
  if ( peek == "++" || peek == "--" ) {
    token = GetToken() ;                        // ++ or --
    ucode = ucode + " " + token ;

    token = GetToken();                         // ID
    if ( !Is_ID( token ) ) Error( token );
    ucode = ucode + " " + token ;

    Rest_of_PPMM_Identifier_started_basic_exp();
  } // if
  else if ( peek == "+" || peek == "-" || peek == "!" ) {
    token = GetToken();                         // sign
    ucode = ucode + " " + token ;

    peek = PeekToken();
    while ( peek == "+" || peek == "-" || peek == "!" ) {
      token = GetToken();
      ucode = ucode + " " + token ;
      peek = PeekToken();
    } // while

    Signed_unary_exp();
    Romce_and_romloe();
  } // if
  else if ( peek == "(" ) {
    token = GetToken();                         // "("
    ucode = ucode + " " + token ;

    Expression();

    token = GetToken();                         // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token ;

    Romce_and_romloe();
  } // else if
  else if ( Is_Constant( peek ) ) {
    token = GetToken();                         // Constant
    ucode = ucode + " " + token ;

    Romce_and_romloe();
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();                         // ID
    if ( token == "Done" ) ustate = "Done";
    else if ( token == "ListAllVariables" ) ustate = "ListAllVariables";
    else if ( token == "ListAllFunctions" ) ustate = "ListAllFunctions";
    else if ( token == "ListVariable" ) ustate = "ListVariable";
    else if ( token == "ListFunction" ) ustate = "ListFunction";
    else if ( !uisfunction && !SearchID( token ) ) throw new Exception3( token );
    else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
    ucode = ucode + token ;

    Rest_of_Identifier_started_basic_exp();
  } // else if
  else {
    token = GetToken();
    Error( token );
  } // else
} // Basic_expression()

void Rest_of_Identifier_started_basic_exp() {
  // : [ '[' expression ']' ]
  //    ( assignment_operator basic_expression
  //      |
  //      [ PP | MM ] romce_and_romloe
  //    )
  //  | '(' [ actual_parameter_list ] ')' romce_and_romloe

  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    token = GetToken();                          // "("
    ucode = ucode + token;

    peek = PeekToken();
    if ( peek != ")" ) Actual_parameter_list();

    token = GetToken();                          // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token;

    Romce_and_romloe();
  } // if
  else {
    if ( peek == "[" ) {
      token = GetToken();                        // "["
      ucode = ucode + token;

      Expression();

      token = GetToken();                        // "]"
      if ( token != "]" ) Error( token );
      ucode = ucode + " " + token;

      peek = PeekToken();
    } // if

    if ( Assignment_operator( peek ) ) {
      token = GetToken();                       // "=" or "+=" or "-=" or "*=" or "/=" or "%="
      ucode = ucode + " " + token;

      Basic_expression();
    } // if
    else {
      if ( peek == "++" || peek == "--" ) {
        token = GetToken();
        ucode = ucode + " " + token;
      } // if

      Romce_and_romloe();
    } // else
  } // else
} // Rest_of_Identifier_started_basic_exp()

void Rest_of_PPMM_Identifier_started_basic_exp() {
  // : [ '[' expression ']' ] romce_and_romloe
  string peek = PeekToken();
  string token = "";
  if ( peek == "[" ) {
    token = GetToken();                            // "["
    ucode = ucode + " " + token ;

    Expression();

    token = GetToken() ;
    if ( token != "]" ) Error( token );
    ucode = ucode + " " + token ;
  } // if

  Romce_and_romloe();
} // Rest_of_PPMM_Identifier_started_basic_exp()

bool Sign( string token ) {
  // : '+' | '-' | '!'
  if ( token != "+" && token != "-" && token != "!" ) return false;
  return true;
} // Sign()

void Actual_parameter_list() {
  // : basic_expression { ',' basic_expression }
  Basic_expression();
  string peek = PeekToken();
  string token = "";
  while ( peek == "," ) {
    token = GetToken();                   // ","
    ucode = ucode + " " + token ;

    Basic_expression();
    peek = PeekToken();
  } // while()
} // Actual_parameter_list()

bool Assignment_operator( string token ) {
  // : '=' | TE | DE | RE | PE | ME
  if ( token != "=" && token != "+=" && token != "-=" && token != "*=" && token != "/=" && token != "%=" )
    return false;
  return true;
} // Assignment_operator()

void Romce_and_romloe() {
  // : rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]

  Rest_of_maybe_logical_OR_exp();
  string peek = PeekToken();
  string token = "";
  if ( peek == "?" ) {
    token = GetToken();                   // "?"
    ucode = ucode + " " + token;

    Basic_expression();

    token = GetToken();                   // ":"
    if ( token != ":" ) Error( token );
    ucode = ucode + " " + token;

    Basic_expression();
  } // if
} // Romce_and_romloe()

void Rest_of_maybe_logical_OR_exp() {
  // : rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
  Rest_of_maybe_logical_AND_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "||" ) {
    token = GetToken();                   // "||"
    ucode = ucode + " " + token ;

    Maybe_logical_AND_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_logical_OR_exp()

void Maybe_logical_AND_exp() {
  // : maybe_bit_OR_exp { AND maybe_bit_OR_exp }
  Maybe_bit_OR_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "&&" ) {
    token = GetToken() ;                  // "&&"
    ucode = ucode + " " + token;

    Maybe_bit_OR_exp();
    peek = PeekToken();
  } // while()
} // Maybe_logical_AND_exp()

void Rest_of_maybe_logical_AND_exp() {
  // : rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
  Rest_of_maybe_bit_OR_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "&&" ) {
    token = GetToken() ;                  // "&&"
    ucode = ucode + " " + token;

    Maybe_bit_OR_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_logical_AND_exp()

void Maybe_bit_OR_exp() {
  // : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
  Maybe_bit_ex_OR_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "|" ) {
    token = GetToken() ;                  // "|"
    ucode = ucode + " " + token;

    Maybe_bit_ex_OR_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_OR_exp()

void Rest_of_maybe_bit_OR_exp() {
  // : rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
  Rest_of_maybe_bit_ex_OR_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "|" ) {
    token = GetToken() ;                  // "|"
    ucode = ucode + " " + token;

    Maybe_bit_ex_OR_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_OR_exp()

void Maybe_bit_ex_OR_exp() {
  // : maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
  Maybe_bit_AND_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "^" ) {
    token = GetToken() ;                  // "^"
    ucode = ucode + " " + token;

    Maybe_bit_AND_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_ex_OR_exp()

void Rest_of_maybe_bit_ex_OR_exp() {
  // : rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
  Rest_of_maybe_bit_AND_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "^" ) {
    token = GetToken() ;                  // "^"
    ucode = ucode + " " + token;

    Maybe_bit_AND_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_ex_OR_exp()

void Maybe_bit_AND_exp() {
  // : maybe_equality_exp { '&' maybe_equality_exp }
  Maybe_equality_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "&" ) {
    token = GetToken() ;                  // "&"
    ucode = ucode + " " + token;

    Maybe_equality_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_AND_exp()

void Rest_of_maybe_bit_AND_exp() {
  // : rest_of_maybe_equality_exp { '&' maybe_equality_exp }
  Rest_of_maybe_equality_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "&" ) {
    token = GetToken() ;                  // "&"
    ucode = ucode + " " + token;

    Maybe_equality_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_AND_exp()

void Maybe_equality_exp() {
  // : maybe_relational_exp
  //    { ( EQ | NEQ ) maybe_relational_exp}

  Maybe_relational_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "==" || peek == "!=" ) {
    token = GetToken() ;                  // "==" or "!="
    ucode = ucode + " " + token;

    Maybe_relational_exp();
    peek = PeekToken();
  } // while()
} // Maybe_equality_exp()

void Rest_of_maybe_equality_exp() {
  // : rest_of_maybe_relational_exp
  //    { ( EQ | NEQ ) maybe_relational_exp }

  Rest_of_maybe_relational_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "==" || peek == "!=" ) {
    token = GetToken() ;                  // "==" or "!="
    ucode = ucode + " " + token;

    Maybe_relational_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_equality_exp()

void Maybe_relational_exp() {
  // : maybe_shift_exp
  //    { ( '<' | '>' | LE | GE ) maybe_shift_exp }

  Maybe_shift_exp();
  string peek = PeekToken();
  string token = "";
  while (  peek == ">" || peek == "<" || peek == ">=" || peek == "<=" ) {
    token = GetToken() ;                  // ">" or "<" or ">=" or "<="
    ucode = ucode + " " + token;

    Maybe_shift_exp();
    peek = PeekToken();
  } // while()
} // Maybe_relational_exp()

void Rest_of_maybe_relational_exp() {
  // : rest_of_maybe_shift_exp
  //    { ( '<' | '>' | LE | GE ) maybe_shift_exp }

  Rest_of_maybe_shift_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == ">" || peek == "<" || peek == ">=" || peek == "<=" ) {
    token = GetToken() ;                  // ">" or "<" or ">=" or "<="
    ucode = ucode + " " + token;

    Maybe_shift_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_relational_exp()

void Maybe_shift_exp() {
  // : maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
  Maybe_additive_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == ">>" || peek == "<<" ) {
    token = GetToken() ;                  // ">>" or "<<"
    ucode = ucode + " " + token;

    Maybe_additive_exp();
    peek = PeekToken();
  } // while()
} // Maybe_shift_exp()

void Rest_of_maybe_shift_exp() {
  // : rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
  Rest_of_maybe_additive_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == ">>" || peek == "<<" ) {
    token = GetToken() ;                  //  ">>" or "<<"
    ucode = ucode + " " + token;

    Maybe_additive_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_shift_exp()

void Maybe_additive_exp() {
  // : maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
  Maybe_mult_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "+" || peek == "-" ) {
    token = GetToken() ;                  // "+" or "-"
    ucode = ucode + " " + token;

    Maybe_mult_exp();
    peek = PeekToken();
  } // while()
} // Maybe_additive_exp()

void Rest_of_maybe_additive_exp() {
  // : rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
  Rest_of_maybe_mult_exp();
  string peek = PeekToken();
  string token = "";
  while ( peek == "+" || peek == "-" ) {
    token = GetToken() ;                  //  "+" or "-"
    ucode = ucode + " " + token;

    Maybe_mult_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_additive_exp()

void Maybe_mult_exp() {
  // : unary_exp rest_of_maybe_mult_exp
  Unary_exp();
  Rest_of_maybe_mult_exp();
} // Maybe_mult_exp()

void Rest_of_maybe_mult_exp() {
  // : { ( '*' | '/' | '%' ) unary_exp }  // could be empty !
  string peek = PeekToken();
  string token = "";
  while ( peek == "*" || peek == "/" || peek == "%" ) {
    token = GetToken();                   //  "*" or "/" or "%"
    ucode = ucode + " " + token;

    Unary_exp();
    peek = PeekToken();
  } // while
} // Rest_of_maybe_mult_exp()

void Unary_exp() {
  // : sign { sign } signed_unary_exp
  //  | unsigned_unary_exp
  //  | ( PP | MM ) Identifier [ '[' expression ']' ]

  string peek = PeekToken();
  string token = "";
  if ( peek == "++" || peek == "--" ) {
    token = GetToken();                    // "++" or "--"
    ucode = ucode + " " + token;

    token = GetToken();                    // ID
    if ( !uisfunction && !SearchID( token ) ) throw new Exception3( token );
    else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
    ucode = ucode + " " + token;

    peek = PeekToken();
    if ( peek == "[" ) {
      token = GetToken();                  // "["
      ucode = ucode + " " + token;

      Expression() ;

      token = GetToken();
      if ( token != "]" ) Error( token );  // "]"
      ucode = ucode + " " + token;
    } // if
  } // if
  else if ( Sign( peek ) ) {
    token = GetToken();                    // sign
    ucode = ucode + " " + token;

    peek = PeekToken();
    while ( Sign( peek ) ) {
      token = GetToken();                  // sign
      ucode = ucode + " " + token;
      peek = PeekToken();
    } // while()

    Signed_unary_exp();
  } // else if
  else
    Unsigned_unary_exp();

} // Unary_exp()

void Signed_unary_exp() {
  // : Identifier [ '(' [ actual_parameter_list ] ')'
  //                 |
  //                 '[' expression ']'
  //               ]
  //  | Constant
  //  | '(' expression ')'

  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    token = GetToken();                      // "("
    ucode = ucode + " " + token;

    Expression();

    token = GetToken();                      // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token;
  } // if
  else if ( Is_Constant( peek ) ) {
    token = GetToken();                      // Constant
    ucode = ucode + " " + token ;
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();                      // ID
    if ( !uisfunction && !SearchID( token ) ) throw new Exception3( token );
    else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
    ucode = ucode + " " + token;

    peek = PeekToken();
    if ( peek == "(" ) {
      token = GetToken();                    // "("
      ucode = ucode + " " + token;

      peek = PeekToken();
      if ( peek != ")" ) Actual_parameter_list();

      token = GetToken();                    // ")"
      ucode = ucode + " " + token;
    } // if
    else if ( peek == "[" ) {
      token = GetToken();                    // "["
      ucode = ucode + " " + token;

      Expression();

      token = GetToken();                    // "]"
      if ( token != "]" ) Error( token );
      ucode = ucode + " " + token;
    } // else if
  } // else if
  else {
    token = GetToken();
    Error( token );
  } // else
} // Signed_unary_exp()

void Unsigned_unary_exp() {
  // : Identifier [ '(' [ actual_parameter_list ] ')'
  //                 |
  //                 [ '[' expression ']' ] [ ( PP | MM ) ]
  //               ]
  // | Constant
  // | '(' expression ')'

  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    token = GetToken();                       // "("
    ucode = ucode + " " + token ;

    Expression();

    token = GetToken();                       // ")"
    if ( token != ")" ) Error( token );
    ucode = ucode + " " + token ;
  } // if
  else if ( Is_Constant( peek ) ) {
    token = GetToken();
    ucode = ucode + " " + token ;
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();                       // ID
    if ( !uisfunction && !SearchID( token ) ) throw new Exception3( token );
    else if ( uisfunction && !Search_FID( token ) ) throw new Exception3( token );
    ucode = ucode + " " + token ;

    peek = PeekToken();
    if ( peek == "(" ) {
      token = GetToken();                     // "("
      ucode = ucode + " " + token ;

      peek = PeekToken();
      if ( peek != ")" ) Actual_parameter_list();

      token = GetToken();                     // ")"
      if ( token != ")" ) Error( token );
      ucode = ucode + " " + token ;
    } // if
    else if ( peek == "[" ) {
      token = GetToken();                     // "["
      ucode = ucode + " " + token ;

      Expression();

      token = GetToken();                     // "]"
      if ( token != "]" ) Error( token );
      ucode = ucode + " " + token ;

      peek = PeekToken();
      if ( peek == "++" || peek == "--" ) {
        token = GetToken();
        ucode = ucode + " " + token ;
      } // if
    } // else if
    else if ( peek == "++" || peek == "--" ) {
      token = GetToken();
      ucode = ucode + " " + token ;
    } // else if
  } // else if
  else {
    token = GetToken();
    Error( token );
  } // else
} // Unsigned_unary_exp()

bool SearchID( string token ) {
  for ( int i = 0 ; i < uparameter.size() ; i++ ) {
    if ( uparameter[i].name == token ) return true;
  } // for

  for ( int i = 0 ; i < ufunction.size() ; i++ ) {
    if ( ufunction[i].name == token ) return true;
  } // for

  if ( token == "ListAllVariables" || token == "ListAllFunctions"
       || token == "ListVariable" || token == "ListFunction" ) return true;

  if ( token == "if" || token == "else" || token == "while" || token == "do" || token == "return" )
    throw new Exception2( token );

  return false;
} // SearchID()

bool Search_FID( string token ) {
  for ( int i = 0 ; i < ut_function.fparameter.size() ; i++ ) {
    if ( ut_function.fparameter[i].name == token ) return true;
  } // for

  for ( int i = 0 ; i < ufunction.size() ; i++ ) {
    if ( ufunction[i].name == token ) return true;
  } // for

  for ( int i = 0 ; i < uparameter.size() ; i++ ) {
    if ( uparameter[i].name == token ) return true;
  } // for

  return false;
} // Search_FID()

bool Is_ID( string token ) {
  char temp[100];
  strcpy( temp, token.c_str( ) );
  for ( int i = 0 ; i < strlen( temp ) ; i++ ) {
    if ( ( temp[i] > 'z' || temp[i] < 'a' ) && ( temp[i] > 'Z' || temp[i] < 'A' )
         && ( temp[i] > '9' || temp[i] < '0' ) && temp[i] != '_' ) return false;
  } // for

  return true;
} // Is_ID()

bool Is_Constant( string token ) {
  char temp[100];
  strcpy( temp, token.c_str( ) );

  if ( ustate == "ListFunction" ) {
    for ( int i = 1 ; i < strlen( temp ) - 1 ; i++ )
      ut_variable.name = ut_variable.name + temp[i];
  } // if

  if ( token == "true" || token == "false" ) return true;
  if ( temp[0] == '\"' && temp[ strlen( temp ) - 1 ] == '\"' ) return true;
  for ( int i = 0 ; i < strlen( temp ) ; i++ ) {
    if ( ( temp[i] < '0' || temp[i] > '9' ) && temp[i] != '.' ) {
      return false;
    } // if
  } // for

  return true;
} // Is_Constant()

void ListAllVariables( ) {
  Variable temp;
  for ( int i = 0 ; i < uparameter.size() ; i++ ) {
    for ( int j = 0 ; j < uparameter.size() ; j++ ) {
      if ( uparameter[i].name < uparameter[j].name ) {
        temp = uparameter[i];
        uparameter[i] = uparameter[j];
        uparameter[j] = temp;
      } // if
    } // for
  } // for

  for ( int i = 0 ; i < uparameter.size( ) ; i++ )
    cout << uparameter[ i ].name << endl;
} // ListAllVariables()

void ListVariable( ) {
  for ( int i = 0 ; i < uparameter.size() ; i++ ) {
    if ( ut_variable.name == uparameter[i].name ) {
      cout << ut_variable.name << endl;
      return ;
    } // if
  } // for
} // ListVariable()

void ListAllFunctions( ) {
  Function temp;
  for ( int i = 0 ; i < ufunction.size( ) ; i++ ) {
    for ( int j = 0 ; j < ufunction.size( ) ; j++ ) {
      if ( ufunction[ i ].name < ufunction[ j ].name ) {
        temp = ufunction[ i ];
        ufunction[ i ] = ufunction[ j ];
        ufunction[ j ] = temp;
      } // if
    } // for
  } // for

  for ( int i = 0 ; i < ufunction.size( ) ; i++ )
    cout << ufunction[ i ].name << "()" << endl;
} // ListAllFunctions()

void ListFunction( ) {
  string space = "";
  for ( int i = 0 ; i < ufunction.size() ; i++ ) {
    if ( ut_variable.name == ufunction[i].name ) {
      for ( int j = 0 ; j < ufunction[i].data.size() ; j++ ) {
        if ( ufunction[i].data[j][ufunction[i].data[j].size() - 1 ] == '{' )
          space = space + "  ";
        if ( ufunction[i].data[j][ufunction[i].data[j].size() - 1 ] == '}' )
          space.erase( 0, 2 );

        if ( j == 0 ) cout << ufunction[i].data[j] << endl;
        else cout << space << ufunction[i].data[j] << endl;

      } // for

      return ;
    } // if
  } // for
} // ListFunction()

void Error( string token ) {
  if ( Know( token ) ) throw new Exception2( token );
  else throw new Exception1( token );
} // Error()

bool Know( string id ) {
  if ( ( id >= "a" && id <= "z" ) || ( id >= "A" && id <= "Z" ) || ( id >= "0" && id <= "9" )
       || id == "(" || id == ")" || id == "[" || id == "]" || id == "{" || id == "}"
       || id == "+" || id == "-" || id == "*" || id == "/" || id == "%" || id == "^"
       || id == ">" || id == "<" || id == ">=" || id == "<=" || id == "==" || id == "!="
       || id == "&" || id == "|" || id == "=" || id == "!" || id == "&&" || id == "||"
       || id == "+=" || id == "-=" || id == "*=" || id == "/=" || id == "%=" || id == "++"
       || id == "--" || id == ">>" || id == "<<" || id == ";" || id == "," || id == "?"
       || id == ":" || id == "." ) return true;

  return false;
} // Know()
