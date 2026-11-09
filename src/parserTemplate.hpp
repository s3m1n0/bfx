
template <typename Type, typename Element, typename Return>
class parserTemplate {
 private:
  Type m_data;
  std::size_t pointer;
  virtual Element peek() = 0;
  virtual Element consume() = 0;

 public:
  parserTemplate(/* args */);
  ~parserTemplate();
  Return parse();
};
