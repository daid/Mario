#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <sp2/string.h>
#include <sp2/math/vector.h>
#include <list>

class ISerializable;
class Serializer
{
public:
    Serializer(const sp::string& filename);
    
    bool read(const sp::string& name, ISerializable& object);
    void write(const sp::string& name, ISerializable& object);

    class Handler
    {
    public:
        template<typename T> void operator()(const char* name, T& value)
        {
            processKey(name);
            processType(value);
            processValue(value);
        }
        template<typename T> void operator()(const char* name, std::vector<T>& value)
        {
            processKey(name);
            processTypeID(Type_Vector);
            processType(value[0]);
            if (mode == Mode::Write)
                addUnsignedInt(value.size());
            else if (read_index >= 0)
                value.resize(readUnsignedInt());
            for(auto& it : value)
                processValue(it);
        }
    private:
        Handler(const sp::string& filename);
        ~Handler();

        bool read(const sp::string& name, ISerializable& object);
        void write(const sp::string& name, ISerializable& object);
        bool buildKeyLookup();
        bool readFile();
        
        void processKey(const char* name);
        void skipType(int type_id);

        void processType(int& value) { processTypeID(Type_Int); }
        template<class T, class = typename std::enable_if<std::is_enum<T>::value>::type> void processType(T& value) { processTypeID(Type_Int); }
        void processType(float& value) { processTypeID(Type_Float); }
        void processType(double& value) { processTypeID(Type_Double); }
        void processType(sp::Vector2f& value) { processTypeID(Type_Vector2f); }
        void processType(sp::Vector2d& value) { processTypeID(Type_Vector2d); }
        void processType(sp::Vector3f& value) { processTypeID(Type_Vector3f); }
        void processType(sp::Vector3d& value) { processTypeID(Type_Vector3d); }
        void processType(sp::string& value) { processTypeID(Type_String); }
        void processType(ISerializable& value) { processTypeID(Type_Object); }
        
        void processTypeID(int id);

        void processValue(int& value) { if (mode == Mode::Write) addSignedInt(value); if (mode == Mode::Read && read_index >= 0) value = readSignedInt(); }
        template<class T, class = typename std::enable_if<std::is_enum<T>::value>::type> void processValue(T& value) { if (mode == Mode::Write) addSignedInt(int(value)); if (mode == Mode::Read && read_index >= 0) value = T(readSignedInt()); }
        void processValue(float& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(double& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(sp::Vector2f& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(sp::Vector2d& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(sp::Vector3f& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(sp::Vector3d& value) { processDataBlock(&value, sizeof(value)); }
        void processValue(sp::string& value);
        void processValue(ISerializable& value);

        void addUnsignedInt(int number);
        int readUnsignedInt();
        void addSignedInt(int number);
        int readSignedInt();
        void processDataBlock(void* data, int size);
        int addToStringTable(const sp::string& str);

        enum class Mode
        {
            Unknown,
            Read,
            Write
        };
        static constexpr int Type_Int = 0x00;
        static constexpr int Type_Float = 0x01;
        static constexpr int Type_Double = 0x02;
        static constexpr int Type_Vector2i = 0x10;
        static constexpr int Type_Vector2f = 0x11;
        static constexpr int Type_Vector2d = 0x12;
        static constexpr int Type_Vector3i = 0x20;
        static constexpr int Type_Vector3f = 0x21;
        static constexpr int Type_Vector3d = 0x22;
        static constexpr int Type_String = 0x40;
        static constexpr int Type_Vector = 0x41;
        static constexpr int Type_Object = 0x42;

        Mode mode = Mode::Unknown;
        sp::string filename;

        std::map<sp::string, int> string_table_lookup;
        std::vector<sp::string> string_table;
        std::vector<std::vector<uint8_t>> data_blocks;
        int current_data_block = -1;
        std::map<int, int> main_objects;
        std::map<sp::string, int> key_lookup;
        int read_index;
    
        friend class Serializer;
    };

private:
    Handler handler;
};

class ISerializable
{
public:
    virtual ~ISerializable() {}

    virtual void serialize(Serializer::Handler& handler) = 0;
};


#endif//SERIALIZER_H
