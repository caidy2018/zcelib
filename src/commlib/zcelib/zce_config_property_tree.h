/*!
* @copyright  2004-2013  Apache License, Version 2.0 FULLSAIL
* @filename   zce_config_property_tree.h
* @author     Sailzeng <sailerzeng@gmail.com>
* @version
* @date       2011年10月5日
* @brief      一个保存配置信息的数，通过path访问node上的信息，
*
*
* @details    这个类的最终实现目标是实现类似BOOST ，Property Tree 和 ACE_Configuration_Heap
*             类的目标，将配置信息组织成一棵树存放
*
*
*
* @note      今天IPhone 5没有发布，而是发布了一款Iphone 4S,广大果粉有点失望
*
*
*/


#ifndef ZCE_LIB_CONFIG_PROPERTY_TREE_H_
#define ZCE_LIB_CONFIG_PROPERTY_TREE_H_

//
//
class ZCE_Sockaddr_In;
class ZCE_Sockaddr_In6;
class ZCE_Time_Value;





/*!
* @brief      配置文件读取后存放的树
*             其他读取工具读取数据内容后都生成放入ZCE_Conf_PropertyTree中，
*             思路还是和Property Tree基本一致。
* @note       2013年回头仔细看了BOOST的说明，发现人家的实现比我考虑的还是完整不
*             少，最后还是向其靠拢了。
*/
class ZCE_Conf_PropertyTree
{
protected:

    ///叶子节点
    typedef std::string  LEAF_NOTE_TYPE;

    ///子树的节点的类型,这儿不是map，所以不是高效实现，但为啥不用map呢，我估计是
    ///因为其实map本事并不了顺序，所以在还原的时候，会完全混乱原来的数据，（虽然
    ///并不错），所以
    typedef std::list< std::pair<std::string, ZCE_Conf_PropertyTree> > CHILDREN_NOTE_TYPE;

    //
public:

    ///构造函数
    ZCE_Conf_PropertyTree();
    ~ZCE_Conf_PropertyTree();


    ///根据路径得到一个CHILD 子树，
    int path_get_child(const std::string &path_str,
                       ZCE_Conf_PropertyTree *& child_data);

    ///根据路径得到一个const CHILD 子树，
    int path_get_child(const std::string &path_str,
                       const ZCE_Conf_PropertyTree *& child_data) const;

    //取得叶子节点的string
    int get_leafptr(const std::string &path_str,
                    std::string *& leaf_data);

    int get_leafptr(const std::string &path_str,
                    const std::string *& leaf_data) const;

    /*!
    * @brief      还是用了特化的模板高点这一组函数,模板函数,依靠特化实现,
    * @tparam     val_type 被特化成 ZCE_Sockaddr_In，ZCE_Sockaddr_In6，ZCE_Time_Value
    *             int32_t ,int64_t,std::string, 等。
    * @return     int      是否正常的读取倒了配置
    * @param      path_str 读取的路径
    * @param      val      读取返回的值
    */
    template<typename val_type>
    int path_get_leaf(const std::string &path_str,
                      val_type &val) const;


    template<>
    int path_get_leaf(const std::string &path_str,
                      ZCE_Sockaddr_In &val) const;

    ///取得IPV6的地址，
    template<>
    int path_get_leaf(const std::string &path_str,
                      ZCE_Sockaddr_In6 &val) const;

    ///时间戳字符串，使用ISO的格式
    template<>
    int path_get_leaf(const std::string &path_str,
                      ZCE_Time_Value &val) const;


    ///增加一个新的CHILD,当然里面全部数据为NULL,并且返回新增的节点
    void add_child(const std::string &key_str,
                  ZCE_Conf_PropertyTree *&new_child_note);

    ///还是用了特化的模板高点这一组函数,模板函数,只定义不实现
    template<typename val_type>
    void set_leaf(val_type val);


    //放入一个叶子节点，string
    template<>
    void set_leaf(const std::string &value_data);

    //放入一个叶子节点，int
    template<>
    void set_leaf(int value_int);

    //放入一个叶子节点，bool
    template<>
    void set_leaf(bool value_bool);


    //
    template<typename val_type>
    void add_child_leaf(const std::string &key_str,
        val_type val)
    {
        ZCE_Conf_PropertyTree *tree_node = NULL;
        add_child(key_str, tree_node);
        tree_node->set_leaf<val_type>(val);
    }

public:
    ///设置分割符号,允许你更换这个
    static void set_separator(char separator_char);

protected:

    ///默认使用.作为风格符号，考虑到name里面可能会使用这个符号，
    ///所以这儿也可以让你改,没有用const ，而且提供了修改函数
    static char  SEPARATOR_STRING[2];

protected:

    ///叶子节点的MAP
    LEAF_NOTE_TYPE   leaf_node_;

    ///子树节点的MAP
    CHILDREN_NOTE_TYPE     child_node_;

};

#endif //ZCE_LIB_CONFIG_PROPERTY_H_

