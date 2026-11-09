template <typename Type, typename Return>
class ParserTemplate {
 protected:
  Type& m_data;
  std::size_t m_pointer = 0;

  auto peek() const { return m_data[m_pointer]; }

  auto consume() { return m_data[m_pointer++]; }

  bool eof() const { return m_pointer >= m_data.size(); }

 public:
  explicit Parser(Type& data) : m_data(data) {}
  virtual ~Parser() = default;

  virtual Return parse() = 0;
};