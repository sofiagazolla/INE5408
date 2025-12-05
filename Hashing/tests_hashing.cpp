#include "gtest/gtest.h"
#include "hashing.h"

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class HashTest: public ::testing::Test {
protected:
	Hash<int> H1;
	Hash<int> H2;
	Hash<int> H3;
    Hash<float> H4;
    Hash<float> H5;
};


TEST_F(HashTest, FromKeys) {
	structures::LinkedList<std::string> L;
	L.push_back("brasil");
	L.push_back("paraguai");
	L.push_back("uruguai");
	L.push_back("argentina");

	H4.fromkeys(L, 1.5);

	H4.insert("peru", 5.0);

    ASSERT_EQ(5u, H4.size());
    ASSERT_EQ(1.5, H4["brasil"]);
    ASSERT_EQ(1.5, H4["paraguai"]);
    ASSERT_EQ(1.5, H4["uruguai"]);
    ASSERT_EQ(1.5, H4["argentina"]);
    ASSERT_EQ(5.0, H4["peru"]);

}


TEST_F(HashTest, Highest) {
	H1.insert("aaa",111); H1.insert("bbb",222);
	H1.insert("ccc",333); H1.insert("ddd",444);
	H1.insert("abc",123); H1.insert("cba",321);
	H1.insert("acb",132);

	H2.insert("aae",666); H2.insert("bbb",777);
	H2.insert("eaa",888); H2.insert("fff",999);

    ASSERT_EQ(4u, H1.highest());
    ASSERT_EQ(3u, H2.highest());
}


TEST_F(HashTest, FirstLetter) {
	H4.insert("brasil", 1.0);
	H4.insert("paraguai", 1.0);
	H4.insert("uruguai", 1.0);
	H4.insert("argentina", 1.0);
	H4.insert("peru", 2.0);

	Hash<float> Ha = H4.firstletter('p');

    ASSERT_EQ(2u, Ha.size());
    ASSERT_EQ(1.0, Ha["paraguai"]);
    ASSERT_EQ(2.0, Ha["peru"]);
    ASSERT_EQ(false, Ha.has_key("brasil"));
    ASSERT_EQ(false, Ha.has_key("uruguai"));
    ASSERT_EQ(false, Ha.has_key("argentina"));

	Hash<float> Hb = H4.firstletter('b');

    ASSERT_EQ(1u, Hb.size());
    ASSERT_EQ(1.0, Hb["brasil"]);
    ASSERT_EQ(false, Hb.has_key("paraguai"));
    ASSERT_EQ(false, Hb.has_key("peru"));
    ASSERT_EQ(false, Hb.has_key("uruguai"));
    ASSERT_EQ(false, Hb.has_key("argentina"));

	Hash<float> Hc = H4.firstletter('z');

    ASSERT_EQ(0u, Hc.size());
}


TEST_F(HashTest, SubSet) {
	structures::LinkedList<std::string> L;
	H4.insert("brasil", 5.0);
	H4.insert("paraguai", 5.0);
	H4.insert("uruguai", 5.0);
	H4.insert("argentina", 5.0);

	H5.insert("uruguai", 9.9);
	H5.insert("brasil", 7.7);
	H5.insert("peru", 5.5);

    ASSERT_EQ(false, H4.subset(H5));

    H5.remove("peru");

    ASSERT_EQ(true, H4.subset(H5));
}


TEST_F(HashTest, Update) {
	H1.insert("aaa",111); H1.insert("bbb",222);
	H1.insert("ccc",333); H1.insert("ddd",444);
	H1.insert("abc",123); H1.insert("cba",321);
	H1.insert("acb",132);

	H2.insert("aaa",666); H2.insert("bbb",777);
	H2.insert("eee",888); H2.insert("fff",999);

	H1.update(H2);

    ASSERT_EQ(9u, H1.size());
    ASSERT_EQ(666, H1["aaa"]);
    ASSERT_EQ(777, H1["bbb"]);
    ASSERT_EQ(333, H1["ccc"]);
    ASSERT_EQ(444, H1["ddd"]);
    ASSERT_EQ(888, H1["eee"]);
    ASSERT_EQ(999, H1["fff"]);
    ASSERT_EQ(123, H1["abc"]);
    ASSERT_EQ(321, H1["cba"]);
    ASSERT_EQ(132, H1["acb"]);

    // ---

    H3.insert("bbb",765);
    H3.insert("zzz",456);
    H3.insert("eee",987);

    H1.update(H3);

    ASSERT_EQ(10u, H1.size());
    ASSERT_EQ(666, H1["aaa"]);
    ASSERT_EQ(765, H1["bbb"]);
    ASSERT_EQ(333, H1["ccc"]);
    ASSERT_EQ(444, H1["ddd"]);
    ASSERT_EQ(987, H1["eee"]);
    ASSERT_EQ(999, H1["fff"]);
    ASSERT_EQ(123, H1["abc"]);
    ASSERT_EQ(321, H1["cba"]);
    ASSERT_EQ(132, H1["acb"]);
    ASSERT_EQ(456, H1["zzz"]);
}
