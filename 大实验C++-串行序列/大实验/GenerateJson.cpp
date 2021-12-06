/* 实现GenerateJson.h中的类方法 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <unordered_map>
#include <map>
#include <random>
#include "GenerateJson.h"
#include "util.h"

using namespace boost::property_tree;
//default_random_engine e(time(NULL));