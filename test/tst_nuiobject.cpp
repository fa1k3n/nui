#include <gtest/gtest.h>

#include <core/NUIObject>
#include <core/NUIApp>

class IPainterMock : public IPainter {
 public:
        void init() {}
};;

TEST(TestSuite, testBasicCreate) {
    NUI::NUIObject obj;
    
    EXPECT_TRUE(true);
}

TEST(TestSuite, testBasicCreateWithParent) {
    IPainterMock painter;
    NUI::NUIApp app(&painter);
    NUI::NUIObject parent, obj(&parent);
    
    EXPECT_TRUE();
}

