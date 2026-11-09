template <typename Type, typename Element, typename Return>
class Parser {
 protected:
  Type& m_data;
  std::size_t m_pointer = 0;

  virtual Element peek() const = 0;
  virtual Element consume() = 0;

 public:
  explicit Parser(Type& data) : m_data(data) {}

  virtual ~Parser() = default;

  virtual Return parse() = 0;
};