// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLauncher.h"

#include<vector>
using namespace std;


// Sets default values for this component's properties
UMapLauncher::UMapLauncher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMapLauncher::BeginPlay()
{
	Super::BeginPlay();
	InitializeMap();
	// ...
	 
}
// Called every frame
void UMapLauncher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#define F float
template<typename T>
struct Point {
	T x, y, z;
};
void InitializeMap() {
	auto map = MapProductor().getMap();
	PositionTranslator trans;
	for (int i = 0;i < map.size();i++) {
		for (int j = 0;j < map[i].size();j++) {
			for (int k = 0;k <= map[i][j];k++) {
				CreateStone(trans.transFromDispersedToContinuous( Point<int>{
					i, j, k
				}));
			}
		}
	}
}

void CreateStone(Point<F> pos) {
	//预设需要根据PositionTranslator的HEIGHT和EDGEWEIGHT进行纵向和平面拉伸

}



class PositionTranslator {
private:
	constexpr static F HEIGHT = 1.0;
	constexpr static F EDGEWEIGHT = 1.0;
public:


	Point<F> transFromDispersedToContinuous(Point<int> p) {
		Point<F>ans;
		ans.z = p.z * HEIGHT + HEIGHT / 2.0;
		ans.y = (p.y - 0.5 * (p.x & 1)) * sqrt(3) * EDGEWEIGHT;
		ans.x = p.x * 1.5 * EDGEWEIGHT;
		return ans;
	}
};
#define mk(a,b) make_pair(a,b)
class MapProductor {
private:
	constexpr static pair<int, int>BLOCK_SIZE = mk(4, 4);//一个block中包含的stone的个数
	constexpr static pair<int, int>MAP_SIZE = mk(4, 4);//一张地图中包含的block个数
	constexpr static int MAP_HEIGHT = 16;//地图高度,以stone高度为单位
	class Perlin {
	public:
		float persistence;
		int Number_Of_Octaves;
		int seed;
		Perlin(int S) {
			persistence = 0.;
			Number_Of_Octaves = 4;
			seed = S;
		}

		double Noise(int x, int y)    // 根据(x,y)获取一个初步噪声值
		{
			int n = x + y * 57;
			n = (n << 13) ^ n;
			return //rand()*1.0/RAND_MAX;
				(1.0 - ((n * (n * n * 15731 + 789221) + seed) & 0x7fffffff) / 1073741824.0);
		}

		double SmoothedNoise(int x, int y)   //光滑噪声
		{
			double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
			double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
			double center = Noise(x, y) / 4;
			return corners + sides + center;
		}
		double Cosine_Interpolate(double a, double b, double x)  // 余弦插值
		{
			double ft = x * 3.1415927;
			double f = (1 - cos(ft)) * 0.5;
			return a * (1 - f) + b * f;
		}
		double Linear_Interpolate(double a, double b, double x) //线性插值
		{
			return a * (1 - x) + b * x;
		}

		double InterpolatedNoise(float x, float y)   // 获取插值噪声
		{
			int integer_X = int(x);
			float  fractional_X = x - integer_X;
			int integer_Y = int(y);
			float fractional_Y = y - integer_Y;
			double v1 = SmoothedNoise(integer_X, integer_Y);
			double v2 = SmoothedNoise(integer_X + 1, integer_Y);
			double v3 = SmoothedNoise(integer_X, integer_Y + 1);
			double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
			double i1 = Cosine_Interpolate(v1, v2, fractional_X);
			double i2 = Cosine_Interpolate(v3, v4, fractional_X);
			return Cosine_Interpolate(i1, i2, fractional_Y);
		}

		double PerlinNoise(float x, float y)    // 最终调用：根据(x,y)获得其对应的PerlinNoise值
		{
			double noise = 0;
			double p = persistence;
			int n = Number_Of_Octaves;
			for (int i = 0; i < n; i++)
			{
				double frequency = pow(2, i);
				double amplitude = pow(p, i);
				noise = noise + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
			}

			return noise;
		}
	};
public:
	static vector<vector<int>> getMap(int seed = 1349880437) {
		Perlin P(seed);
		pair<int, int>size = mk(BLOCK_SIZE.first * MAP_SIZE.first, BLOCK_SIZE.second * MAP_SIZE.second);
		vector<vector<double>>v(size.first, vector<double>(size.second));
		vector<vector<int>>map(size.first, vector<int>(size.second));
		double mx = -1e9, mn = 1e9;
		for (int i = 0;i < size.first;i++) {
			for (int j = 0;j < size.second;j++) {
				double tp = P.PerlinNoise(i, j);
				v[i][j] = tp;
				mx = max(tp, mx);
				mn = min(tp, mn);
			}
		}
		//      cout<<mx<<" "<<mn<<endl;
		for (int i = 0;i < size.first;i++) {
			for (int j = 0;j < size.second;j++) {
				map[i][j] = (v[i][j] - mn) / (mx - mn) * MAP_HEIGHT;
				//     printf("%d ",map[i][j]);
			}
			//   puts("");
		}
		return map;
	}

};
#undef F
#undef mk