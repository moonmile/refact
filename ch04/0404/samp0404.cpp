#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>


/**
 * 以下の2つの関数をひとつのクラスにまとめる
 */

// 加算する関数
int add( int a, int b ) {
    return a + b;
}
// 乗算する関数
int mul( int a, int b ) {
    return a * b;
}


/**
 * 一つのクラスにまとめた場合
 */
class MyClass {
public:
    int add( int a, int b ) {
        return a + b;
    }
    int mul( int a, int b ) {
        return a * b;
    }
};



class MyClassTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MyClassTest);
    CPPUNIT_TEST(testFunction1);
    CPPUNIT_TEST(testFunction2);
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(MyClassTest);

int main() {
    // Run the tests
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();

    return 0;
}