#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>


/**
 * クラスにメソッドを追加する
 */
class MyClass {
public:
    int add( int a, int b ) {
        return a + b;
    }
    int mul( int a, int b ) {
        return a * b;
    }
    int dev( int a, int b ) {
        if ( b == 0 ) {
            return 0;
        }
        return a / b;
    }
};


class Person {
    private:
        std::string name;
        int age;
        int height;
    public:
        Person( std::string name, int age, int height ) {
            this->name = name;
            this->age = age;
            this->height = height;
        }
        std::string getName() {
            return this->name;
        }
        int getAge() {
            return this->age;
        }
        std::string toString() {
            return "Name: " + this->name + ", Age: " + std::to_string(this->age) + ", Height: " + std::to_string(this->height);
        }
};





class MyClassTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MyClassTest);
    CPPUNIT_TEST(testFunction1);
    CPPUNIT_TEST(testFunction2);
    CPPUNIT_TEST(testFunction3);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFunction1() {
        MyClass myObject;
        
        // Test the behavior of add function
        CPPUNIT_ASSERT_EQUAL( 3, myObject.add( 1, 2 ) );
        CPPUNIT_ASSERT_EQUAL( 7, myObject.add( 3, 4 ) );
        CPPUNIT_ASSERT_EQUAL( 11, myObject.add( 5, 6 ) );
    }

    void testFunction2() {
        MyClass myObject;
        // Test the behavior of mul funciton 
        CPPUNIT_ASSERT_EQUAL( 2, myObject.mul( 1, 2 ) );
        CPPUNIT_ASSERT_EQUAL( 12, myObject.mul( 3, 4 ) );
        CPPUNIT_ASSERT_EQUAL( 30, myObject.mul( 5, 6 ) );
    }

    void testFunction3() {
        MyClass myObject;
        // Test the behavior of dev funciton 
        CPPUNIT_ASSERT_EQUAL( 2, myObject.dev( 2, 1 ) );
        CPPUNIT_ASSERT_EQUAL( 3, myObject.dev( 6, 2 ) );
        CPPUNIT_ASSERT_EQUAL( 5, myObject.dev( 10, 2 ) );
        // 0除算のチェック
        CPPUNIT_ASSERT_EQUAL( 0, myObject.dev( 10, 0 ) );
    }
};


class testPerson : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testPerson);
    CPPUNIT_TEST(testInit);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(demo);
    CPPUNIT_TEST_SUITE_END();
public:
    void testInit() {
        Person *person = new Person("Taro", 20, 170);
        CPPUNIT_ASSERT_EQUAL( std::string("Taro"), person->getName() );
        CPPUNIT_ASSERT_EQUAL( 20, person->getAge() );
    }
    void testToString() {
        Person *person = new Person("Taro", 20, 170);
        CPPUNIT_ASSERT_EQUAL( std::string("Name: Taro, Age: 20, Height: 170"), person->toString() );
    }

    // デモ用のテスト
    void demo() {
        Person *person = new Person("Taro", 20, 170);
        CPPUNIT_ASSERT_EQUAL( std::string("Taro"), person->getName() );
        CPPUNIT_ASSERT_EQUAL( std::string("Name: Taro, Age: 20, Height: 170"), person->toString() );
        Person *person2 = new Person(std::string("Hanako"), 18, 160);
        CPPUNIT_ASSERT_EQUAL( std::string("Hanako"), person2->getName() );
        CPPUNIT_ASSERT_EQUAL( std::string("Name: Hanako, Age: 18, Height: 160"), person2->toString() );
    }
};



CPPUNIT_TEST_SUITE_REGISTRATION(MyClassTest);
CPPUNIT_TEST_SUITE_REGISTRATION(testPerson);

int main() {
    // Run the tests
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();

    return 0;
}