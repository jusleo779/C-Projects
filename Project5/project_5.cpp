#include <initializer_list>
#include <iostream>
#include <cassert>

/**********************************************************************************
 * README 
 * ********************************************************************************
 * This starter code is a skeleton of the Set and Node classes.
 * You can modify this code to create your project_5 submission.
 * Any main() function or output will be ignoed by testing software.
 * A testing main() can be found on Learn.
 * 
 * From Project 5 Specification: 2.1 Development Stratigies
 * "First, implement the node class and all of its member functions. This should be
 *  straight-forward from the course notes, as they are the sam member functions as 
 *  for a linked list.
 * 
 *  Second, start with a skeleton, where each member function is defined, but where
 *  the default values of the return type is returned. ..."
 * 
 * The skeleton has been povided (below) for you to modify.
*/

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );
 
  /////////////////////////////
 /// Set class declaration ///
/////////////////////////////
class Set {
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();
 
    // The instructions will describe exactly what to do
    Set( Set const &orig );//copy constructor
    Set( Set      &&orig );//move constructor
 
    // The instructions will describe exactly what to do
    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );
 
    // Size operations
    bool        empty() const;
    std::size_t size()  const;
 
    // Clear all items out of the set
    void clear();
 
    // Find the value item in the set
    //  - Return the address of the node if found,
    //    and nullptr otherwise.
    Node *find( int const &item ) const;
 
    // Insert the item into the set if it
    // is not already in the set.
    //  - Return 1 if the item is new,
    //    and 0 otherwise.
    std::size_t insert( int const &item );
 
    // Insert all the items in the array
    // from array[begin] to array[end - 1]
    // that are not already in the set.
    //  - Return the number of items inserted
    //    into the set.
    std::size_t insert( int         const array[],
                        std::size_t const begin,
                        std::size_t const end );
 
    // Remove the item from the set and
    // return the number of items removed.
    std::size_t erase( int const &item );
 
    // Move any items from 'other', whose values
    // do not appear in 'this', to 'this'
    // Leave any items that already appear
    // in 'this' and 'other' in 'other'. 
    std::size_t merge( Set &other );

 
    // Set findoperations
    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );
 
    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;
 
    // Returns 'true' if the 'other' set
    // is a subset of 'this' set; that is,
    // all entries in the 'other' set are
    // also in this set.
    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;
 
    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;
   
  private:
    Node *p_head_;
 
  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};


  ///////////////////////////////
 /// Node class declaration  ///
///////////////////////////////
class Node {
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;
    void setNext(Node *const next);
 
  private:
    int   value_;
    Node *next_;

  // Allow any member function in the class
  // 'Set' to access or modify the member
  // variables of any instance of this class.
  friend class Set;
};

 
  ///////////////////////////////
 /// Node class Definition   ///
///////////////////////////////

// Node constructor
Node::Node( int new_value, Node *new_next ):
value_{new_value},
next_{new_next} {
  
}
 
int Node::value() const {
  return value_;
}

Node *Node::next() const {
  return next_;
}
void Node::setNext(Node *const next){
  next_ = next;
}


  ///////////////////////////////
 /// Set class definition    ///
///////////////////////////////

// Initializing constructor
Set::Set( std::initializer_list<int> initial_values):
 p_head_{nullptr}{
  for(int const &value : initial_values){
    insert(value);
  }
}

// Destructor
Set::~Set() {
  clear();
}
 
// Copy constructor
Set::Set( Set const &orig ) {
    this -> p_head_ = nullptr;
    for(Node *ptr {orig.p_head_}; ptr != nullptr; ptr = ptr -> next()){
    this -> insert(ptr -> value());
    }
  
}

// Move constructor
Set::Set( Set &&orig ) {
  std::swap(p_head_, orig.p_head_);
  orig.p_head_ = nullptr;
}
 
// Copy assignment
Set &Set::operator=( Set const &orig ) {
  if(this == &orig){
    return *this;
  }
  else{
    clear();
    for(Node *ptr {orig.p_head_}; ptr != nullptr; ptr = ptr -> next()){
      this -> insert(ptr -> value());
    }
  }
  return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig ) {
  std::swap(p_head_, orig.p_head_); 
  orig.p_head_ = nullptr;
  return *this;
}
 
// Empty
bool Set::empty() const {
  if(p_head_ == nullptr){
    return true;
  }
  return false;
}

// Size
std::size_t Set::size() const {
  size_t size = 0;
  for(Node *p_node = p_head_; p_node != nullptr; p_node = p_node -> next()){
    size++;
  }
  return size;
}
 
 
// Clear
void Set::clear() {
  while(!empty()){
    Node *p_head_old = p_head_;
    p_head_ = p_head_ -> next();
    delete p_head_old;
    p_head_old = nullptr;
  }
}
 
// Find
Node *Set::find( int const &item ) const {
  if(p_head_ == nullptr){
    return nullptr;
  }
  Node *val = p_head_;
  while(val != nullptr){
    if(val -> value() == item){
      return val;
    }
    else{
      val = val -> next();
    }
  }
  return nullptr;
}
 
// Insert the item into the set
std::size_t Set::insert( int const &item ) {
  if(p_head_ == nullptr){
    p_head_ = new Node(item, nullptr);
    return 1;
  } 
  else if(find(item) == nullptr){
    Node *new_node = new Node(item, p_head_);
    p_head_ = new_node;
    return 1;
  }
  return 0;
}
 
// Insert all the items in the array
std::size_t Set::insert( int         const array[],
                         std::size_t const begin,
                         std::size_t const end ) {
  std::size_t count = 0;
  for(int i = begin; i < end; i++){
    if(insert(array[i]) == 1){
      count++;
    }
    insert(array[i]);
  }
  return count;
}

 
// Remove the item from the set and
// return the number of items removed.
std::size_t Set::erase( int const &item ) {
  Node *check = find(item);
  if(check == nullptr){
    return 0;
  }else{
    if(check == p_head_){
      Node *p_old_head = p_head_;
      p_head_ = p_head_ -> next();
      delete p_old_head;
      p_old_head = nullptr;
    }else{
      Node *val = p_head_;
      while (val != nullptr) {
        if (val -> next() == check) {
          Node *val_remove = val -> next();
          val -> setNext(val_remove -> next());
          delete val_remove;
        }
        val = val -> next();
      }
    }
    return 1;
  }
  return 0; 
}
 
// Move any items from 'other', whose values
// do not appear in 'this', to 'this'.
// Leave any items that already appear
// in both sets, in both sets. 
std::size_t Set::merge( Set &other ) {
  std::size_t count{ 0 };
  Node* o = other.p_head_;
  while(o != nullptr && o -> next() != nullptr) {
    if(!this -> find(o -> value())){
      Node* move = o;
      o = o -> next();
      other.p_head_ = o;
      move -> setNext(p_head_);
      p_head_ = move;
      count++;
    }
    else if(!this -> find(o -> next() -> value())){
      Node *move = o -> next(); 
      o -> setNext( move -> next());
      move -> setNext(p_head_);
      p_head_ = move;
      count++;
    }
    else{
      o = o -> next();
    }
  }
  return count;
}

  //////////////////////
 /// Set operations ///
//////////////////////
Set &Set::operator|=( Set const &other ) {
  Node *o = other.p_head_;
  while(o != nullptr){
    this -> insert(o -> value());
    o = o -> next();
  }
  return *this;
}
 
Set &Set::operator&=( Set const &other ) {
  Node *val = p_head_;
  while( val != nullptr){
    if(other.find( val -> value()) == nullptr){
      Node *prev = val;
      val =  val -> next();
      erase(prev -> value());
    }else{
      val =  val -> next();
    }
  }
  return *this;
}
 
Set &Set::operator^=( Set const &other ) {
  Node *o = other.p_head_;
  while(o != nullptr){
    if(this -> find(o -> value())){
      Node *prev = o;
      o = o -> next();
      erase(prev -> value());
    }
    else{
      insert(o -> value());
      o = o -> next();
    }
    
  }
  return *this;
}
 
Set &Set::operator-=( Set const &other ) {
  Node *val = this -> p_head_;
  while(val != nullptr){
    Node *next = val -> next();
    if(other.find(val -> value())){
      erase(val -> value());
    }
    val = next;
  }
  return *this;
}
 
Set Set::operator|( Set const &other ) const {
  Set result{*this};
  result |= other;
  return result;
}
 
Set Set::operator&( Set const &other ) const {
  Set result{*this};
  result &= other;
  return result;
}
 
Set Set::operator^( Set const &other ) const {
  Set result{*this};
  result ^= other;
  return result;
}
 
Set Set::operator-( Set const &other ) const {
  Set result{*this};
  result -= other;
  return result;
}
 
// Returns 'true' if the 'other' set
// is a subset of 'this' set; that is,
// all entries in the 'other' set are
// also in this set.
bool Set::operator>=( Set const &other ) const {
  Node *o = other.p_head_;
  while(o != nullptr){
    if(!this -> find(o -> value())){
      return false;
    }
    else{
      o = o -> next();
    }
  }
  return true;
}
 
bool Set::operator<=( Set const &other ) const {
  return other >= *this;
}
 
bool Set::operator>( Set const &other ) const {
  Node *o = other.p_head_;
  while(o != nullptr){
    if(!this -> find(o ->value_) ){
      return false;
    }
    else{
      o = o -> next();
    }
  }
  if(this -> size() != other.size())
  {
    return true;
  }
  return false;
}
 
bool Set::operator<( Set const &other ) const {
  return other > *this;
}
 
bool Set::operator==( Set const &other ) const {
  if(operator<=(other) && operator>=(other)){
    return true;
  }
  return false;
}
 
bool Set::operator!=( Set const &other ) const {
  return !(operator==(other));
}


  ////////////////////////////////////////////
 /// Supplied Code for print Set objects  ///
////////////////////////////////////////////
/// @brief Overloads the << operator allowing the print of Set objects
/// @param out The ostream to print to (e.g. std::cout <<)
/// @param rhs The Set to print (e.g. << set_A)
/// @note You do not need to edit or alter this code
std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
  out << "{";
  if ( !rhs.empty() ) {
    out << rhs.p_head_->value();   
    for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
      out << ", " << ptr->value();
    }
  }
  out << "}";
 
  return out;
}


