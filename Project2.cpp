# include <iostream>
# include <stdlib.h> // exit( 0 )
# include <string.h> // strcpy, strlen
# include <vector>   // vector
# include <string>

using namespace std;

struct Variable {
  string type;
  string name;
  string size;
};

struct Function {
  string type;
  string name;
  vector< Variable> parameter;
  vector< string > body;
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

vector< vector<string> > gInput_list;
vector< string > gToken_list;
vector< Variable > gparameter ;
vector< Variable > gBuffer_parameter;
vector< Function > gFunction;
bool gcom_state ;
string gstate;
int gLine ;

void Run( bool isPrint, string name ) ;
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
void ListVariable( string token ) ;
void ListAllFunctions( ) ;
void ListFunction( string token ) ;
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
      cout << "> " ;
      gLine = 1;
      gstate = "";
      gcom_state = false;
      gBuffer_parameter.clear();
      gToken_list.clear();
      User_input( );

      gInput_list.push_back( gToken_list );
    } // try
    catch ( Exception1 * e ) {
      cout << "Line " << gLine << " : unrecognized token with first char : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception2 * e ) {
      cout << "Line " << gLine << " : unexpected token : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception3 * e ) {
      cout << "Line " << gLine << " : undefined identifier : '" << e->mMsg << "'" << endl;
      cin.getline( trash, 256 );
    } // catch
    catch ( Exception4 * e ) {
      cout << "Line " << gLine << " : Error" << endl;
      cin.getline( trash, 256 );
    } // catch
  } // while()

  return 0 ;
} // main()

void Run( bool isPrint, string name ) {
  isPrint = false;
  if ( isPrint )
    cout << "Function name : " << name << endl;
} // Run()

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
      peek = cin.peek();
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
      if ( c == '\n' ) gLine++;
      else if ( c == '/' ) {
        char c2 = cin.peek( );
        if ( c2 == '/' ) {
          cin.getline( trash, 256 ); // is comment
          gLine++;
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
    else if ( peek == '\'' ) {
      c = cin.get();
      name = name + c ;
      c = cin.get();
      name = name + c ;
      c = cin.peek();
      if ( c == '\'' ) {
        c = cin.get();
        name = name + c;
      } // if

      return name ;
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
  while ( a == ' ' || a == '\t' ) a = cin.get( );

  if ( a == '/' ) {
    char b = cin.peek( );
    if ( b == '/' ) {
      char trash[ 256 ];
      cin.getline( trash, 256 );
      gLine++;
    } // if
    else cin.putback( a );
  } // if
  else if ( a == '\n' ) gLine++;
  else cin.putback( a );
} // Skip_comment()

void User_input( ) {
  // : ( definition | statement ) { definition | statement }

  Run( false, "User_input" );
  string peek = PeekToken();
  if ( peek == "void" || peek == "int" || peek == "char"
       || peek == "float" || peek == "string" || peek == "bool" ) {
    Definition();

    if ( gToken_list[2] == "(" ) {
      Function functemp ;
      functemp.body = gToken_list;
      functemp.type = gToken_list[0];
      functemp.name = gToken_list[1];

      for ( int i = 3 ; gToken_list[i] != ")" ;  ) {
        Variable temp;

        temp.type = gToken_list[i];
        i = i + 1 ;
        if ( Is_ID( gToken_list[i] ) ) {
          temp.name = gToken_list[i];
          i = i + 1;
        } // if

        if ( gToken_list[i] == "[" ) {
          temp.size = gToken_list[ i + 1 ];
          i = i + 4;
        } // if
        else if ( gToken_list[i] == ")" ) ;
        else i = i + 1 ;

        // gBuffer_parameter.push_back( temp );
        functemp.parameter.push_back( temp );
      } // for

      bool isfind = false;
      for ( int i = 0 ; i < gFunction.size() ; i++ ) {
        if ( gFunction[i].name == gToken_list[1] ) {
          gFunction[i].parameter = gBuffer_parameter ;
          gFunction[i].body = gToken_list;
          cout << "New definition of " << gToken_list[1] << "() entered ..." << endl;
          isfind = true;
        } // if
      } // for

      if ( !isfind ) {
        gFunction.push_back( functemp );
        cout << "Definition of " << gToken_list[1] << "() entered ..." << endl;
      } // if
    } // if
    else {
      Variable temp ;
      temp.type = gToken_list[0];
      temp.size = "";
      for ( int i = 1 ; i < gToken_list.size() ; i++ ) {
        if ( Is_ID( gToken_list[ i ] ) ) {
          if ( SearchID( gToken_list[ i ] ) ) {
            temp.name = gToken_list[i];
            for ( int j = 0 ; j < gparameter.size() ; j++ ) {
              if ( gparameter[ j ].name == gToken_list[ i ] ) {
                gparameter[ j ].type = gToken_list[0];
                if ( i + 2 < gToken_list.size() && Is_Constant( gToken_list[ i + 2 ] ) ) {
                  i = i + 2;
                  temp.size = gToken_list[ i ] ;
                } // if
              } // if
            } // for

            cout << "New definition of " << temp.name << " entered ..." << endl ;
          } // if
          else {
            temp.name = gToken_list[i] ;
            if ( i + 2 < gToken_list.size() && Is_Constant( gToken_list[ i + 2 ] ) ) {
              i = i + 2;
              temp.size = gToken_list[ i ] ;
            } // if

            gparameter.push_back( temp );
            cout << "Definition of " << temp.name << " entered ..." << endl ;
          } // else

        } // if
      } // for
    } // else
  } // if
  else {
    Statement();
    cout << "Statement executed ..." << endl;
  } // else

  Skip_comment() ;
} // User_input()

void Definition() {
  // :           VOID Identifier function_definition_without_ID
  // | type_specifier Identifier function_definition_or_declarators

  Run( false, "Definition" );
  string name = "", peek = PeekToken();
  if ( peek == "void" ) {
    gToken_list.push_back( GetToken() );                // "void"
    name = GetToken();                                  // "ID"
    if ( !Is_ID( name ) ) Error( name );
    else gToken_list.push_back( name );

    Function_definition_without_ID();
  } // if
  else {
    gToken_list.push_back( Type_specifier() );          // "int", "char", "float", "string", "bool"
    name = GetToken();                // "ID"
    if ( !Is_ID( name ) ) Error( name );
    else gToken_list.push_back( name );

    peek = PeekToken();
    if ( peek == "(" )   // this is function definition
      Function_definition_without_ID();
    else                  // variable declaration
      Rest_of_declarators();
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

  Run( false, "Rest_of_declarators" );
  string peek = PeekToken();
  string token = "";

  if ( peek == "[" ) {
    gToken_list.push_back( GetToken() );   // "["

    token = GetToken();                    //  Constant
    if ( !Is_Constant( token ) ) Error( token );
    else gToken_list.push_back( token );

    token = GetToken();                    // "]"
    if ( token != "]" ) Error( token );
    else gToken_list.push_back( token );

    peek = PeekToken();
  } // if()


  while ( peek == "," ) {
    gToken_list.push_back( GetToken() );   // ","

    token = GetToken();                    //  ID
    if ( !Is_ID( token ) ) Error( token );
    else gToken_list.push_back( token );

    peek = PeekToken() ;
    if ( peek == "[" ) {
      gToken_list.push_back( GetToken() );   // "["

      token = GetToken();                    //  Constant
      if ( !Is_Constant( token ) ) Error( token );
      else gToken_list.push_back( token );

      token = GetToken();                    // "]"
      if ( token != "]" ) Error( token );
      else gToken_list.push_back( token );
    } // if

    peek = PeekToken();
  } // while()

  token = GetToken();                       // ";"
  if ( token != ";" ) Error( token );
  else gToken_list.push_back( token );
} // Rest_of_declarators()

void Function_definition_without_ID( ) {
  // : '(' [ VOID | formal_parameter_list ] ')' compound_statement

  Run( false, "Function_definition_without_ID" );
  string peek = "", token = GetToken();             // "("
  if ( token == "(" ) {
    gToken_list.push_back( token );
    peek = PeekToken();
    if ( peek == "void" )                // "void"
      gToken_list.push_back( GetToken() );
    else if ( peek == "int" || peek == "char" || peek == "float"
              || peek == "string" || peek == "bool" )
      Formal_parameter_list();

    token = GetToken();                   // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token );

    Compound_statement();
  } // if()
  else Error( token );
} // Function_definition_without_ID()

void Formal_parameter_list() {
  // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ]
  // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }

  Run( false, "Formal_parameter_list" );
  Variable temp;
  temp.type = Type_specifier();
  gToken_list.push_back( temp.type );  // type
  string token = "";
  string peek = PeekToken();

  if ( peek == "&" ) gToken_list.push_back( GetToken() );  // "&"

  temp.name = GetToken();                          // ID
  if ( !Is_ID( temp.name ) ) Error( temp.name );
  else gToken_list.push_back( temp.name );

  peek = PeekToken();
  if ( peek == "[" ) {
    gToken_list.push_back( GetToken() );   // "["

    temp.size = GetToken();                    //  Constant
    if ( !Is_Constant( temp.size ) ) Error( temp.size );
    else gToken_list.push_back( temp.size );

    token = GetToken();                    // "]"
    if ( token != "]" ) Error( token );
    else gToken_list.push_back( token );

    peek = PeekToken();
  } // if()

  gBuffer_parameter.push_back( temp );
  temp.size = "";
  while ( peek == "," ) {
    gToken_list.push_back( GetToken() );             // ","
    temp.type = Type_specifier() ;
    gToken_list.push_back( temp.type );  // type

    peek = PeekToken();
    if ( peek == "&" ) gToken_list.push_back( GetToken() );  // "&"

    temp.name = GetToken();                         // ID
    if ( !Is_ID( temp.name ) ) Error( temp.name );
    else gToken_list.push_back( temp.name );

    peek = PeekToken();
    if ( peek == "[" ) {
      gToken_list.push_back( token );           // "["

      temp.size = GetToken();                        // Constant
      if ( !Is_Constant( temp.size ) ) Error( temp.size );
      else gToken_list.push_back( temp.size );

      token = GetToken();                        // "]"
      if ( token != "]" ) Error( token );
      else gToken_list.push_back( token );

      peek = PeekToken();
    } // if

    gBuffer_parameter.push_back( temp );
    temp.size = "";
  } // while()
} // Formal_parameter_list()

void Compound_statement() {
  // : '{' { declaration | statement } '}'

  Run( false, "Compound_statement" );
  string token = GetToken();
  if ( token != "{" ) Error( token );            // "{"
  else gToken_list.push_back( token );

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
  else gToken_list.push_back( token );
} // Compound_statement()

void Declaration() {
  // : type_specifier Identifier rest_of_declarators

  Run( false, "Declaration" );
  Variable temp;
  string name = "";
  gToken_list.push_back( Type_specifier() );              // type

  temp.name = GetToken();                    // ID
  if ( !Is_ID( temp.name ) ) Error( temp.name );
  else gToken_list.push_back( temp.name );

  // 進入Rest_of_declarators前記錄位置
  // 為了將變數放到gBuffer_parameter
  Rest_of_declarators();
  temp.type = gToken_list[0];
  for ( int i = 1; i < gToken_list.size() ; i++ ) {

    if ( Is_ID( gToken_list[i] ) ) temp.name = gToken_list[i] ;
    if ( gToken_list[i] == "[" ) {
      temp.size = gToken_list[i + 1];
      i = i + 2;
    } // if

    if ( gToken_list[i] == "," || gToken_list[i] == ";" )
      gBuffer_parameter.push_back( temp );

    temp.size = "";
  } // for
} // Declaration()

void Statement() {
  // : ';'     // the null statement
  //  | expression ';'   // expression here should not be empty
  //  | RETURN [ expression ] ';'
  //  | compound_statement
  //  | IF '(' expression ')' statement [ ELSE statement ]
  //  | WHILE '(' expression ')' statement
  //  | DO statement WHILE '(' expression ')' ';'

  Run( false, "Statement" );
  string peek = PeekToken();
  string token = "";
  if ( peek == ";" ) {
    gToken_list.push_back( GetToken() );
    return ;
  } // if
  else if ( peek == "return" ) {
    gToken_list.push_back( GetToken() );        // return
    peek = PeekToken();

    if ( peek != ";" ) Expression();

    token = GetToken();                         // ";"
    if ( token != ";" ) Error( token );
    else gToken_list.push_back( token );
  } // else if
  else if ( peek == "{" ) Compound_statement();
  else if ( peek == "if" ) {
    gToken_list.push_back( GetToken() );                         // if

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    else gToken_list.push_back( token );

    Expression( );

    token = GetToken();
    if ( token != ")" ) Error( token );         // ")"
    else gToken_list.push_back( token );

    Statement();

    peek = PeekToken();
    if ( peek == "else" ) {
      token = GetToken();                       // else
      gToken_list.push_back( token );
      Statement();
    } // if
  } // else if
  else if ( peek == "while" ) {
    gToken_list.push_back( GetToken() );                         // while

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    else gToken_list.push_back( token ) ;

    Expression();

    token = GetToken();
    if ( token != ")" ) Error( token );         // ")"
    else gToken_list.push_back( token );

    Statement();

  } // else if
  else if ( peek == "do" ) {
    gToken_list.push_back( GetToken() );        // "do"

    Statement();

    token = GetToken();                         // while
    if ( token != "while" ) Error( token );
    else gToken_list.push_back( token ) ;

    token = GetToken();                         // "("
    if ( token != "(" ) Error( token );
    else gToken_list.push_back( token ) ;

    Expression();

    token = GetToken();                         // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token ) ;

    token = GetToken();                         // ";"
    if ( token != ";" ) Error( token );
    else gToken_list.push_back( token ) ;
  } // else if
  else {
    if ( peek == "cin" ) {                       // deal with "cin"
      gToken_list.push_back( GetToken() );

      token = GetToken();                       // ">>"
      if ( token != ">>" ) Error( token );
      else gToken_list.push_back( token ) ;

      Expression();
    } // if
    else if ( peek == "cout" ) {                 // deal with "cout"
      gToken_list.push_back( GetToken() );       // "cout"

      token = GetToken();                        // "<<"
      if ( token != "<<" ) Error( token );
      else gToken_list.push_back( token );

      Expression();
    } // else if
    else if ( peek == "Done" || peek == "ListAllVariables" || peek == "ListAllFunctions"
              || peek == "ListVariable" || peek == "ListFunction" ) {
      token = GetToken();
      gToken_list.push_back( token ) ;       // ID
      if ( token == "Done" ) gstate = "Done";
      else if ( token == "ListAllVariables" ) gstate = "ListAllVariables";
      else if ( token == "ListAllFunctions" ) gstate = "ListAllFunctions";
      else if ( token == "ListVariable" ) gstate = "ListVariable";
      else if ( token == "ListFunction" ) gstate = "ListFunction";

      Rest_of_Identifier_started_basic_exp();
    } // else if
    else
      Expression();

    token = GetToken();                         // ";"

    if ( token != ";" ) Error( token );
    else gToken_list.push_back( token );

    if ( gstate == "Done" ) {
      cout << "Our-C exited ..." << endl;
      // system( "pause" ) ;
      exit( 0 ) ;
    } // if
    else if ( gstate == "ListAllVariables" ) ListAllVariables( );
    else if ( gstate == "ListAllFunctions" ) ListAllFunctions( );
    else if ( gstate == "ListVariable" ) {
      for ( int i = 0 ; i < gToken_list.size() ; i++ ) {
        if ( Is_Constant( gToken_list[i] ) ) ListVariable( gToken_list[i] ) ;
      } // for
    } // else if
    else if ( gstate == "ListFunction" ) {
      for ( int i = 0 ; i < gToken_list.size() ; i++ ) {
        if ( Is_Constant( gToken_list[i] ) ) ListFunction( gToken_list[i] ) ;
      } // for
    } // else if
  } // else
} // Statement()

void Expression() {
  // basic_expression { ',' basic_expression }

  Run( false, "Expression" );
  Basic_expression();
  string peek = PeekToken();
  while ( peek == "," ) {
    gToken_list.push_back( GetToken() );                  // ","
    Basic_expression();
    peek = PeekToken();
  } // while
} // Expression()

void Basic_expression() {
  // : Identifier rest_of_Identifier_started_basic_exp
  //  | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
  //  | sign { sign } signed_unary_exp romce_and_romloe
  //  | ( Constant | '(' expression ')' ) romce_and_romloe

  Run( false, "Basic_expression" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "++" || peek == "--" ) {
    gToken_list.push_back( GetToken() ) ;                        // ++ or --

    token = GetToken();                         // ID
    if ( Is_ID( token ) ) {
      if ( SearchID( token ) ) gToken_list.push_back( token ) ;
      else throw new Exception3( token );
    } // if
    else Error( token ) ;

    Rest_of_PPMM_Identifier_started_basic_exp();
  } // if
  else if ( peek == "+" || peek == "-" || peek == "!" ) {
    gToken_list.push_back( GetToken() ) ;       // sign

    peek = PeekToken();
    while ( peek == "+" || peek == "-" || peek == "!" ) {
      gToken_list.push_back( GetToken() ) ;     // sign
      peek = PeekToken();
    } // while

    Signed_unary_exp();
    Romce_and_romloe();
  } // else if
  else if ( peek == "(" ) {
    gToken_list.push_back( GetToken() ) ;       // "("

    Expression();

    token = GetToken();                         // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token );

    Romce_and_romloe();
  } // else if
  else if ( Is_Constant( peek ) ) {
    gToken_list.push_back( GetToken() ) ;       // Constant
    Romce_and_romloe();
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();
    if ( !SearchID( token ) ) throw new Exception3( token );
    else gToken_list.push_back( token ) ;       // ID

    Rest_of_Identifier_started_basic_exp();
  } // else if
  else Error( GetToken() );
} // Basic_expression()

void Rest_of_Identifier_started_basic_exp() {
  // : [ '[' expression ']' ]
  //    ( assignment_operator basic_expression
  //      |
  //      [ PP | MM ] romce_and_romloe
  //    )
  //  | '(' [ actual_parameter_list ] ')' romce_and_romloe

  Run( false, "Rest_of_Identifier_started_basic_exp" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    gToken_list.push_back( GetToken() );         // "("

    peek = PeekToken();
    if ( peek != ")" ) Actual_parameter_list();

    token = GetToken();                          // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token );

    Romce_and_romloe();
  } // if
  else {
    if ( peek == "[" ) {
      gToken_list.push_back( GetToken() );       // "["

      Expression();

      token = GetToken();                        // "]"
      if ( token != "]" ) Error( token );
      else gToken_list.push_back( token );

      peek = PeekToken();
    } // if

    if ( Assignment_operator( peek ) ) {
      gToken_list.push_back( GetToken() );       // "=" or "+=" or "-=" or "*=" or "/=" or "%="
      Basic_expression();
    } // if
    else {
      if ( peek == "++" || peek == "--" )
        gToken_list.push_back( GetToken() );

      Romce_and_romloe();
    } // else
  } // else
} // Rest_of_Identifier_started_basic_exp()

void Rest_of_PPMM_Identifier_started_basic_exp() {
  // : [ '[' expression ']' ] romce_and_romloe

  Run( false, "Rest_of_PPMM_Identifier_started_basic_exp" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "[" ) {
    gToken_list.push_back( GetToken() );               // "["

    Expression();

    token = GetToken() ;
    if ( token != "]" ) Error( token );
    else gToken_list.push_back( token );
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

  Run( false, "Actual_parameter_list" );
  Basic_expression();
  string peek = PeekToken();
  string token = "";
  while ( peek == "," ) {
    gToken_list.push_back( GetToken() );         // ","

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

  Run( false, "Romce_and_romloe" );
  Rest_of_maybe_logical_OR_exp();
  string peek = PeekToken();
  string token = "";
  if ( peek == "?" ) {
    gToken_list.push_back( GetToken() );        // "?"

    Basic_expression();

    token = GetToken();                         // ":"
    if ( token != ":" ) Error( token );
    else gToken_list.push_back( token );

    Basic_expression();
  } // if
} // Romce_and_romloe()

void Rest_of_maybe_logical_OR_exp() {
  // : rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }

  Run( false, "Rest_of_maybe_logical_OR_exp" );
  Rest_of_maybe_logical_AND_exp();
  string peek = PeekToken();
  while ( peek == "||" ) {
    gToken_list.push_back( GetToken() );       // "||"

    Maybe_logical_AND_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_logical_OR_exp()

void Maybe_logical_AND_exp() {
  // : maybe_bit_OR_exp { AND maybe_bit_OR_exp }

  Run( false, "Maybe_logical_AND_exp" );
  Maybe_bit_OR_exp();
  string peek = PeekToken();
  while ( peek == "&&" ) {
    gToken_list.push_back( GetToken() );       // "&&"

    Maybe_bit_OR_exp();
    peek = PeekToken();
  } // while()
} // Maybe_logical_AND_exp()

void Rest_of_maybe_logical_AND_exp() {
  // : rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }

  Run( false, "Rest_of_maybe_logical_AND_exp" );
  Rest_of_maybe_bit_OR_exp();
  string peek = PeekToken();
  while ( peek == "&&" ) {
    gToken_list.push_back( GetToken() );       // "&&"

    Maybe_bit_OR_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_logical_AND_exp()

void Maybe_bit_OR_exp() {
  // : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

  Run( false, "Maybe_bit_OR_exp" );
  Maybe_bit_ex_OR_exp();
  string peek = PeekToken();
  while ( peek == "|" ) {
    gToken_list.push_back( GetToken() );       // "|"

    Maybe_bit_ex_OR_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_OR_exp()

void Rest_of_maybe_bit_OR_exp() {
  // : rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

  Run( false, "Rest_of_maybe_bit_OR_exp" );
  Rest_of_maybe_bit_ex_OR_exp();
  string peek = PeekToken();
  while ( peek == "|" ) {
    gToken_list.push_back( GetToken() );         // "|"

    Maybe_bit_ex_OR_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_OR_exp()

void Maybe_bit_ex_OR_exp() {
  // : maybe_bit_AND_exp { '^' maybe_bit_AND_exp }

  Run( false, "Maybe_bit_ex_OR_exp" );
  Maybe_bit_AND_exp();
  string peek = PeekToken();
  while ( peek == "^" ) {
    gToken_list.push_back( GetToken() );         // "^"

    Maybe_bit_AND_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_ex_OR_exp()

void Rest_of_maybe_bit_ex_OR_exp() {
  // : rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }

  Run( false, "Rest_of_maybe_bit_ex_OR_exp" );
  Rest_of_maybe_bit_AND_exp();
  string peek = PeekToken();
  while ( peek == "^" ) {
    gToken_list.push_back( GetToken() );         // "^"

    Maybe_bit_AND_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_ex_OR_exp()

void Maybe_bit_AND_exp() {
  // : maybe_equality_exp { '&' maybe_equality_exp }

  Run( false, "Maybe_bit_AND_exp" );
  Maybe_equality_exp();
  string peek = PeekToken();
  while ( peek == "&" ) {
    gToken_list.push_back( GetToken() );         // "&"

    Maybe_equality_exp();
    peek = PeekToken();
  } // while()
} // Maybe_bit_AND_exp()

void Rest_of_maybe_bit_AND_exp() {
  // : rest_of_maybe_equality_exp { '&' maybe_equality_exp }

  Run( false, "Rest_of_maybe_bit_AND_exp" );
  Rest_of_maybe_equality_exp();
  string peek = PeekToken();
  while ( peek == "&" ) {
    gToken_list.push_back( GetToken() );          // "&"

    Maybe_equality_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_bit_AND_exp()

void Maybe_equality_exp() {
  // : maybe_relational_exp
  //    { ( EQ | NEQ ) maybe_relational_exp}

  Run( false, "Maybe_equality_exp" );
  Maybe_relational_exp();
  string peek = PeekToken();
  while ( peek == "==" || peek == "!=" ) {
    gToken_list.push_back( GetToken() );         // "==" or "!="

    Maybe_relational_exp();
    peek = PeekToken();
  } // while()
} // Maybe_equality_exp()

void Rest_of_maybe_equality_exp() {
  // : rest_of_maybe_relational_exp
  //    { ( EQ | NEQ ) maybe_relational_exp }

  Run( false, "Rest_of_maybe_equality_exp" );
  Rest_of_maybe_relational_exp();
  string peek = PeekToken();
  while ( peek == "==" || peek == "!=" ) {
    gToken_list.push_back( GetToken() );         // "==" or "!="

    Maybe_relational_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_equality_exp()

void Maybe_relational_exp() {
  // : maybe_shift_exp
  //    { ( '<' | '>' | LE | GE ) maybe_shift_exp }

  Run( false, "Maybe_relational_exp" );
  Maybe_shift_exp();
  string peek = PeekToken();
  while (  peek == ">" || peek == "<" || peek == ">=" || peek == "<=" ) {
    gToken_list.push_back( GetToken() );        // ">" or "<" or ">=" or "<="

    Maybe_shift_exp();
    peek = PeekToken();
  } // while()
} // Maybe_relational_exp()

void Rest_of_maybe_relational_exp() {
  // : rest_of_maybe_shift_exp
  //    { ( '<' | '>' | LE | GE ) maybe_shift_exp }

  Run( false, "Rest_of_maybe_relational_exp" );
  Rest_of_maybe_shift_exp();
  string peek = PeekToken();
  while ( peek == ">" || peek == "<" || peek == ">=" || peek == "<=" ) {
    gToken_list.push_back( GetToken() );        // ">" or "<" or ">=" or "<="

    Maybe_shift_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_relational_exp()

void Maybe_shift_exp() {
  // : maybe_additive_exp { ( LS | RS ) maybe_additive_exp }

  Run( false, "Maybe_shift_exp" );
  Maybe_additive_exp();
  string peek = PeekToken(), token = "";
  while ( peek == ">>" || peek == "<<" ) {
    token = GetToken();
    if ( ( gToken_list[0] == "cin" && peek == ">>" )
         || ( gToken_list[0] == "cout" && peek == "<<" ) )
      gToken_list.push_back( token );        //  ">>" or "<<"
    else Error( token );

    Maybe_additive_exp();
    peek = PeekToken();
  } // while()
} // Maybe_shift_exp()

void Rest_of_maybe_shift_exp() {
  // : rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }

  Run( false, "Rest_of_maybe_shift_exp" );
  Rest_of_maybe_additive_exp();
  string peek = PeekToken();
  string token ;
  while ( peek == ">>" || peek == "<<" ) {
    token = GetToken();
    if ( ( gToken_list[0] == "cin" && peek == ">>" )
         || ( gToken_list[0] == "cout" && peek == "<<" ) )
      gToken_list.push_back( token );        //  ">>" or "<<"
    else Error( token );

    Maybe_additive_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_shift_exp()

void Maybe_additive_exp() {
  // : maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }

  Run( false, "Maybe_additive_exp" );
  Maybe_mult_exp();
  string peek = PeekToken();
  while ( peek == "+" || peek == "-" ) {
    gToken_list.push_back( GetToken() );        // "+" or "-"

    Maybe_mult_exp();
    peek = PeekToken();
  } // while()
} // Maybe_additive_exp()

void Rest_of_maybe_additive_exp() {
  // : rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }

  Run( false, "Rest_of_maybe_additive_exp" );
  Rest_of_maybe_mult_exp();
  string peek = PeekToken();
  while ( peek == "+" || peek == "-" ) {
    gToken_list.push_back( GetToken() );        //  "+" or "-"

    Maybe_mult_exp();
    peek = PeekToken();
  } // while()
} // Rest_of_maybe_additive_exp()

void Maybe_mult_exp() {
  // : unary_exp rest_of_maybe_mult_exp

  Run( false, "Maybe_mult_exp" );
  Unary_exp();
  Rest_of_maybe_mult_exp();
} // Maybe_mult_exp()

void Rest_of_maybe_mult_exp() {
  // : { ( '*' | '/' | '%' ) unary_exp }  // could be empty !

  Run( false, "Rest_of_maybe_mult_exp" );
  string peek = PeekToken();
  while ( peek == "*" || peek == "/" || peek == "%" ) {
    gToken_list.push_back( GetToken() );        //  "*" or "/" or "%"

    Unary_exp();
    peek = PeekToken();
  } // while
} // Rest_of_maybe_mult_exp()

void Unary_exp() {
  // : sign { sign } signed_unary_exp
  //  | unsigned_unary_exp
  //  | ( PP | MM ) Identifier [ '[' expression ']' ]

  Run( false, "Unary_exp" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "++" || peek == "--" ) {
    gToken_list.push_back( GetToken() );         // "++" or "--"

    token = GetToken();                          // ID
    if ( Is_ID( token ) ) {
      if ( !SearchID( token ) ) throw new Exception3( token );
      else gToken_list.push_back( token );
    } // if
    else Error( token );

    peek = PeekToken();
    if ( peek == "[" ) {
      gToken_list.push_back( GetToken() );       // "["

      Expression() ;

      token = GetToken();
      if ( token != "]" ) Error( token );        // "]"
      else gToken_list.push_back( token );
    } // if
  } // if
  else if ( Sign( peek ) ) {
    gToken_list.push_back( GetToken() );         // sign

    peek = PeekToken();
    while ( Sign( peek ) ) {
      gToken_list.push_back( GetToken() );       // sign
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

  Run( false, "Signed_unary_exp" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    gToken_list.push_back( GetToken() );        // "("

    Expression();

    token = GetToken();                          // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token );
  } // if
  else if ( Is_Constant( peek ) ) {
    gToken_list.push_back( GetToken() );         // Constant
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();                          // ID
    if ( !SearchID( token ) ) throw new Exception3( token );
    gToken_list.push_back( token );

    peek = PeekToken();
    if ( peek == "(" ) {
      gToken_list.push_back( GetToken() );       // "("

      peek = PeekToken();
      if ( peek != ")" ) Actual_parameter_list();

      token = GetToken();                        // ")"
      if ( token != ")" ) Error( token );
      else gToken_list.push_back( token );
    } // if
    else if ( peek == "[" ) {
      gToken_list.push_back( GetToken() );       // "["

      Expression();

      token = GetToken();                        // "]"
      if ( token != "]" ) Error( token );
      else gToken_list.push_back( token );
    } // else if
  } // else if
  else Error( GetToken() );

} // Signed_unary_exp()

void Unsigned_unary_exp() {
  // : Identifier [ '(' [ actual_parameter_list ] ')'
  //                 |
  //                 [ '[' expression ']' ] [ ( PP | MM ) ]
  //               ]
  // | Constant
  // | '(' expression ')'

  Run( false, "Unsigned_unary_exp" );
  string peek = PeekToken();
  string token = "";
  if ( peek == "(" ) {
    gToken_list.push_back( GetToken() );         // "("

    Expression();

    token = GetToken();                          // ")"
    if ( token != ")" ) Error( token );
    else gToken_list.push_back( token );
  } // if
  else if ( Is_Constant( peek ) ) {
    gToken_list.push_back( GetToken() );
  } // else if
  else if ( Is_ID( peek ) ) {
    token = GetToken();                          // ID
    if ( !SearchID( token ) ) throw new Exception3( token );
    gToken_list.push_back( token );

    peek = PeekToken();
    if ( peek == "(" ) {
      gToken_list.push_back( GetToken() );       // "("

      peek = PeekToken();
      if ( peek != ")" ) Actual_parameter_list();

      token = GetToken();                        // ")"
      if ( token != ")" ) Error( token );
      else gToken_list.push_back( token );
    } // if
    else if ( peek == "[" ) {
      gToken_list.push_back( GetToken() );       // "["

      Expression();

      token = GetToken();                     // "]"
      if ( token != "]" ) Error( token );
      else gToken_list.push_back( token );

      peek = PeekToken();
      if ( peek == "++" || peek == "--" )
        gToken_list.push_back( GetToken() );

    } // else if
    else if ( peek == "++" || peek == "--" )
      gToken_list.push_back( GetToken() );
  } // else if
  else Error( GetToken() );
} // Unsigned_unary_exp()


bool SearchID( string token ) {
  for ( int i = 0 ; i < gparameter.size() ; i++ ) {
    if ( gparameter[i].name == token ) return true;
  } // for

  for ( int i = 0 ; i < gBuffer_parameter.size() ; i++ ) {
    if ( gBuffer_parameter[i].name == token ) return true;
  } // for

  for ( int i = 0 ; i < gFunction.size() ; i++ ) {
    if ( gFunction[i].name == token ) return true;
  } // for

  if ( token == "ListAllVariables" || token == "ListAllFunctions"
       || token == "ListVariable" || token == "ListFunction" || token == "Done" )
    return true;

  if ( token == "if" || token == "else" || token == "while" || token == "do" || token == "return" )
    throw new Exception2( token );

  return false;
} // SearchID()

bool Is_ID( string token ) {
  char temp[100];

  strcpy( temp, token.c_str( ) );

  if ( ( temp[0] > 'z' || temp[0] < 'a' ) && ( temp[0] > 'Z' || temp[0] < 'A' ) ) return false;

  for ( int i = 1 ; i < strlen( temp ) ; i++ ) {
    if ( ( temp[i] > 'z' || temp[i] < 'a' ) && ( temp[i] > 'Z' || temp[i] < 'A' )
         && ( temp[i] > '9' || temp[i] < '0' ) && temp[i] != '_' ) return false;
  } // for

  return true;
} // Is_ID()

bool Is_Constant( string token ) {
  char temp[100];
  strcpy( temp, token.c_str( ) );

  if ( token == "true" || token == "false" ) return true;
  if ( temp[0] == '\"' && temp[ strlen( temp ) - 1 ] == '\"' ) return true;
  if ( temp[0] == '\'' && temp[ strlen( temp ) - 1 ] == '\'' ) return true;
  for ( int i = 0 ; i < strlen( temp ) ; i++ ) {
    if ( ( temp[i] < '0' || temp[i] > '9' ) && temp[i] != '.' ) {
      return false;
    } // if
  } // for

  return true;
} // Is_Constant()

void ListAllVariables( ) {
  Variable temp;
  for ( int i = 0 ; i < gparameter.size() ; i++ ) {
    for ( int j = 0 ; j < gparameter.size() ; j++ ) {
      if ( gparameter[i].name < gparameter[j].name ) {
        temp = gparameter[i];
        gparameter[i] = gparameter[j];
        gparameter[j] = temp;
      } // if
    } // for
  } // for

  for ( int i = 0 ; i < gparameter.size( ) ; i++ )
    cout << gparameter[ i ].name << endl;
} // ListAllVariables()

void ListVariable( string token ) {
  token.erase( 0, 1 ) ;
  token.erase( token.length( ) - 1, token.length( ) ) ;

  for ( int i = 0 ; i < gparameter.size() ; i++ ) {
    if ( token == gparameter[i].name ) {
      cout << gparameter[i].type << " " << gparameter[i].name ;
      if ( gparameter[i].size != "" ) {
        cout << "[ " << gparameter[i].size << " ]" ;
      } // if

      cout << " ;" << endl;
      return ;
    } // if
  } // for
} // ListVariable()

void ListAllFunctions( ) {
  Function temp;
  for ( int i = 0 ; i < gFunction.size( ) ; i++ ) {
    for ( int j = 0 ; j < gFunction.size( ) ; j++ ) {
      if ( gFunction[ i ].name < gFunction[ j ].name ) {
        temp = gFunction[ i ];
        gFunction[ i ] = gFunction[ j ];
        gFunction[ j ] = temp;
      } // if
    } // for
  } // for

  for ( int i = 0 ; i < gFunction.size( ) ; i++ )
    cout << gFunction[ i ].name << "()" << endl;

} // ListAllFunctions()

void ListFunction( string token ) {
  token.erase( 0, 1 ) ;
  token.erase( token.length( ) - 1, token.length( ) ) ;

  for ( int i = 0 ; i < gFunction.size() ; i++ ) {
    if ( gFunction[i].name == token ) {
      string space = "";
      cout << gFunction[i].type << " " << gFunction[i].name << "( " ;

      for ( int j = 3 ; j < gFunction[i].body.size() ; j++ ) {
        cout << gFunction[i].body[j] ;


        if ( j + 1 < gFunction[i].body.size() &&
             ( gFunction[i].body[j + 1] == "(" || gFunction[i].body[j + 1] == "["
               || gFunction[i].body[j + 1] == "++" || gFunction[i].body[j + 1] == "--"
               || gFunction[i].body[j + 1] == "," ) ) {
          if ( gFunction[i].body[j] != "if" && gFunction[i].body[j] != "while" ) cout << "";
          else cout << " " ;
        } // if
        else if ( gFunction[i].body[j] == ";" || gFunction[i].body[j] == "{"
                  || gFunction[i].body[j] == "}" )
          cout << "";
        else cout << " ";

        if ( gFunction[i].body[j] == "{" ) space = space + "  ";

        if ( j + 1 < gFunction[i].body.size() && gFunction[i].body[j + 1] == "}" ) {
          space.erase( 0, 2 );
        } // if

        if ( gFunction[i].body[j] == ";" || gFunction[i].body[j] == "{"
             || gFunction[i].body[j] == "}" ) {
          cout << endl << space;
        } // if
      } // for
    } // if
  } // for
} // ListFunction()

void Error( string token ) {
  if ( Know( token ) ) throw new Exception2( token );
  else throw new Exception1( token );
} // Error()

bool Know( string id ) {
  int num = id.length();
  char c_temp[100];
  for ( int j = 0 ; j < id.length() ; j++ )
    c_temp[j] = id[j];

  if ( ( c_temp[0] >= 'a' && c_temp[0] <= 'z' ) || ( c_temp[0] >= 'A' && c_temp[0] <= 'Z' )
       || ( c_temp[0] >= '0' && c_temp[0] <= '9' ) || c_temp[0] == '.' ) return true;

  if ( Is_ID( id ) || Is_Constant( id ) ) return true;

  if ( id == "(" || id == ")" || id == "[" || id == "]" || id == "{" || id == "}"
       || id == "+" || id == "-" || id == "*" || id == "/" || id == "%" || id == "^"
       || id == ">" || id == "<" || id == ">=" || id == "<=" || id == "==" || id == "!="
       || id == "&" || id == "|" || id == "=" || id == "!" || id == "&&" || id == "||"
       || id == "+=" || id == "-=" || id == "*=" || id == "/=" || id == "%=" || id == "++"
       || id == "--" || id == ">>" || id == "<<" || id == ";" || id == "," || id == "?"
       || id == ":" || id == "." || id == "_" || id == "\'" ) return true;

  return false;
} // Know()
