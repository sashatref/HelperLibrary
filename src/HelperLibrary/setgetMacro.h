#pragma once

/*!
  \brief макрос для генерирования set/get функций для Q_PROPERTY
  \param type тип свойства
  \param name_get название функции геттера, указанной в Q_PROPERTY
  \param name_set название фукнции сеттера, указанной в Q_PROPERTY
  \param var_name связанная с свойством функция, которая должна быть объявлена в секции private
  */
#define setget(type, name_get, name_set, var_name) \
    void name_set(type value) \
        {var_name = value;} \
    type name_get() const {return var_name;}


/*!
  \brief макрос для генерирования set/get функций для Q_PROPERTY,
  добавление приватного члена класса, так же прописывает сам макрос Q_PROPERTY
  \param _type тип свойства
  \param member - база для названия члена класса, сеттера/геттера, названия свойства
  имя свойства - <member>
  член класса - m_<member>
  геттер - get_<member>
  сеттер - set_<member>
  */
#define buildProperty(_type, member) \
  public: \
  /**
   * Set member of type _type.
   * @see m_##member for a more detailed description
   */ \
  void set_##member(const _type &_arg_##member) \
  { \
    m_##member = _arg_##member;\
  } \
  /**
   * Get member of type _type.
   * @see m_##member for a more detailed description
   */ \
  const _type &get_##member() const\
  { \
    return m_##member;\
  } \
  private: \
    _type m_##member; \
  Q_PROPERTY(_type member READ get_##member WRITE set_##member) \
  public:

#define buildPropertyPointer(_type, member) \
  public: \
  /**
   * Set member of type _type.
   * @see m_##member for a more detailed description
   */ \
  void set_##member(_type _arg_##member) \
  { \
    m_##member = _arg_##member;\
  } \
  /**
   * Get member of type _type.
   * @see m_##member for a more detailed description
   */ \
  _type get_##member() const\
  { \
    return m_##member;\
  } \
  private: \
    _type m_##member; \
  Q_PROPERTY(_type member READ get_##member WRITE set_##member) \
  public:

#define buildPtrProtected(_type, member) \
  public: \
  /**
   * Set member of type _type.
   * @see m_##member for a more detailed description
   */ \
  void set_##member(_type _arg_##member) \
  { \
    m_##member = _arg_##member;\
  } \
  /**
   * Get member of type _type.
   * @see m_##member for a more detailed description
   */ \
  _type get_##member() const\
  { \
    return m_##member;\
  } \
  protected: \
    _type m_##member; \
  Q_PROPERTY(_type member READ get_##member WRITE set_##member) \
  public:

#define buildPropertyP(_type, member) \
  public: \
  /**
   * Set member of type _type.
   * @see m_##member for a more detailed description
   */ \
  void set_##member(const _type &_arg_##member) \
  { \
    m_##member = _arg_##member;\
  } \
  /**
   * Get member of type _type.
   * @see m_##member for a more detailed description
   */ \
  const _type &get_##member() const\
  { \
    return m_##member;\
  } \
    _type m_##member; \
  Q_PROPERTY(_type member READ get_##member WRITE set_##member) \
  public:

#define buildPropertyD(_type, member, _defaultValue) \
  public: \
  /**
   * Set member of type _type.
   * @see m_##member for a more detailed description
   */ \
  void set_##member(const _type &_arg_##member) \
  { \
    m_##member = _arg_##member;\
  } \
  /**
   * Get member of type _type.
   * @see m_##member for a more detailed description
   */ \
  const _type &get_##member() const\
  { \
    return m_##member;\
  } \
    _type m_##member = _defaultValue; \
  Q_PROPERTY(_type member READ get_##member WRITE set_##member) \
  public:

#define buildPropertyM(_type, member) \
    _type m_##member; \
  Q_PROPERTY(_type member MEMBER m_##member) \
  public:

