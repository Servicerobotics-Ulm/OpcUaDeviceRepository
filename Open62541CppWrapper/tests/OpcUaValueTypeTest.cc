/*
 * OpcUaValueTypeTest.h
 *
 *  Created on: Oct 10, 2018
 *      Author: alexej
 */

#include "OpcUaValueType.hh"
#include <gtest/gtest.h>

namespace OPCUA {

class ValueTypeTest : public ::testing::Test {
protected:
	ValueTypeTest() {
		vi = 10;
		vb = true;
		vd = 3.3;
		vs = std::string("Hello");

		std::vector<int> i_arr(2);
		i_arr[0] = 3;
		i_arr[1] = -7;
		varr_i = i_arr;

		std::vector<bool> b_arr(2);
		b_arr[0] = true;
		b_arr[1] = false;
		varr_b = b_arr;

		std::vector<double> d_arr(3);
		d_arr[0] = -1.0;
		d_arr[1] = 33.3;
		d_arr[2] = .1;
		varr_d = d_arr;

		std::vector<std::string> s_arr(2);
		s_arr[0] = "Hello";
		s_arr[1] = "World";
		varr_s = s_arr;
	}

	ValueType v0;
	ValueType vi;
	ValueType vb;
	ValueType vd;
	ValueType vs;
	ValueType varr_i;
	ValueType varr_b;
	ValueType varr_d;
	ValueType varr_s;
};

TEST_F(ValueTypeTest, EmptynessTest) {
	EXPECT_TRUE(v0.isEmpty());
	EXPECT_FALSE(vi.isEmpty());
	EXPECT_FALSE(vb.isEmpty());
	EXPECT_FALSE(vd.isEmpty());
	EXPECT_FALSE(vs.isEmpty());

	EXPECT_FALSE(varr_i.isEmpty());
	EXPECT_FALSE(varr_b.isEmpty());
	EXPECT_FALSE(varr_d.isEmpty());
	EXPECT_FALSE(varr_s.isEmpty());
}

TEST_F(ValueTypeTest, IsArrayTypeTest) {
	EXPECT_FALSE(v0.isArrayType());
	EXPECT_FALSE(vi.isArrayType());
	EXPECT_FALSE(vb.isArrayType());
	EXPECT_FALSE(vd.isArrayType());
	EXPECT_FALSE(vs.isArrayType());

	EXPECT_TRUE(varr_i.isArrayType());
	EXPECT_TRUE(varr_b.isArrayType());
	EXPECT_TRUE(varr_d.isArrayType());
	EXPECT_TRUE(varr_s.isArrayType());
}

TEST_F(ValueTypeTest, TypeTest) {
	// zero has no type
	EXPECT_FALSE(v0.isIntegerType());
	EXPECT_FALSE(v0.isBooleanType());
	EXPECT_FALSE(v0.isDoubleType());
	EXPECT_FALSE(v0.isStringType());

	// only integer should be true
	EXPECT_TRUE(vi.isIntegerType());
	EXPECT_FALSE(vi.isBooleanType());
	EXPECT_FALSE(vi.isDoubleType());
	EXPECT_FALSE(vi.isStringType());

	// only boolean type should be true
	EXPECT_FALSE(vb.isIntegerType());
	EXPECT_TRUE(vb.isBooleanType());
	EXPECT_FALSE(vb.isDoubleType());
	EXPECT_FALSE(vb.isStringType());

	// only double type should be true
	EXPECT_FALSE(vd.isIntegerType());
	EXPECT_FALSE(vd.isBooleanType());
	EXPECT_TRUE(vd.isDoubleType());
	EXPECT_FALSE(vd.isStringType());

	// only string type should be true
	EXPECT_FALSE(vs.isIntegerType());
	EXPECT_FALSE(vs.isBooleanType());
	EXPECT_FALSE(vs.isDoubleType());
	EXPECT_TRUE(vs.isStringType());

	// test types for array types
	EXPECT_TRUE(varr_i.isIntegerType());
	EXPECT_TRUE(varr_b.isBooleanType());
	EXPECT_TRUE(varr_d.isDoubleType());
	EXPECT_TRUE(varr_s.isStringType());
}

TEST_F(ValueTypeTest, ImplicitCast) {
	int i = vi;
	EXPECT_EQ(i, 10);
	bool b = vb;
	EXPECT_EQ(b, true);
	double d = vd;
	EXPECT_DOUBLE_EQ(d, 3.3);
	std::string s = vs;
	EXPECT_EQ(s, "Hello");
}

TEST_F(ValueTypeTest, ExplicitCast) {
	int i = 0;
	i = static_cast<int>(vi);
	EXPECT_EQ(i, 10);
	bool b = false;
	b = static_cast<bool>(vb);
	EXPECT_EQ(b, true);
	double d = 0.0;
	d = static_cast<double>(vd);
	EXPECT_DOUBLE_EQ(d, 3.3);
	std::string s;
	s = static_cast<const char*>(vs);
	EXPECT_EQ(s, "Hello");
}

TEST_F(ValueTypeTest, ObjectCopyTest) {
	// make a copy using assignment operator
	v0 = vi;
	EXPECT_FALSE(v0.isEmpty());
	// change the value of the first object
	vi = 5;
	int i0 = v0;
	EXPECT_EQ(i0, 10);
	int i1 = vi;
	EXPECT_EQ(i1, 5);

	// copy constructor
	ValueType v2(vs);
	std::string s = v2;
	EXPECT_EQ(s, "Hello");

	ValueType v3;
	EXPECT_TRUE(v3.isEmpty());
	{
		v3 = ValueType(333);
	}
	EXPECT_FALSE(v3.isEmpty());
	int i3 = v3;
	EXPECT_EQ(i3, 333);	
}

TEST_F(ValueTypeTest, ToStringTest) {
	std::string si = vi.toString();
	EXPECT_EQ(si, "10");

	std::string sb = vb.toString();
	EXPECT_EQ(sb, "1");

	std::string sd = vd.toString();
	EXPECT_EQ(sd, "3.3");

	std::string ss = vs.toString();
	EXPECT_EQ(ss, "Hello");
}

TEST_F(ValueTypeTest, ArrayValueTest) {
	// integer array
	std::vector<int> i_arr = varr_i;
	size_t size = 2;
	ASSERT_EQ(i_arr.size(), size);
	EXPECT_EQ(i_arr[0], 3);
	EXPECT_EQ(i_arr[1], -7);

	// boolean array
	std::vector<bool> b_arr = varr_b;
	size = 2;
	ASSERT_EQ(b_arr.size(), size);
	EXPECT_EQ(b_arr[0], true);
	EXPECT_EQ(b_arr[1], false);

	// double array
	std::vector<double> d_arr = varr_d;
	size = 3;
	ASSERT_EQ(d_arr.size(), size);
	EXPECT_EQ(d_arr[0], -1.0);
	EXPECT_EQ(d_arr[1], 33.3);
	EXPECT_EQ(d_arr[2], 0.1);

	// string array
	std::vector<std::string> s_arr = varr_s;
	size = 2;
	ASSERT_EQ(s_arr.size(), size);
	EXPECT_EQ(s_arr[0], "Hello");
	EXPECT_EQ(s_arr[1], "World");
}

TEST_F(ValueTypeTest, NativeTypeTest) {
	ValueType::NativeVariantType type = vi;
	ValueType v2(type);
	int i = v2;
	EXPECT_EQ(i, 10);

	const ValueType::NativeVariantType *ptr = vs;
	ValueType v3(ptr);
	std::string s = v3;
	EXPECT_EQ(s, "Hello");
}

} // end namespace OPCUA

