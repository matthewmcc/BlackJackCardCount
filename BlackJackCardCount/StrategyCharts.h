#include <map>
#include <vector>
#include <string>

#pragma once
class StrategyCharts
{
public:
	StrategyCharts();
	~StrategyCharts();

private:
	std::map<int, std::vector < char >> const SOFT_TOTALS = {
	{ 9, { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S'} },
	{ 8, { 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S'} },
	{ 7, { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' } },
	{ 6, { 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S' } }, 
	{ 5, { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' } },
	{ 4, { 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S' } }, 
	{ 3, { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' } },
	{ 2, { 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S' } } };
};

