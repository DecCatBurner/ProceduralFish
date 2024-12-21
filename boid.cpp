#include "obj.cpp"

class Boid {
    private:
        static inline Cord* boids = nullptr;
        static inline int boidTotal = 0;
        static inline Vector2 rule1 = zerozero, rule2 = zerozero, rule3 = zerozero, rule4 = zerozero;
    public:
        static constexpr int boundDist = -20;
        static constexpr float maxVelo = 3.0f;
        static constexpr float cohesionFactor = 0.001f;
        static constexpr float sight = 25.0f;
        static constexpr float alignmentFactor = 0.00015f;
        static constexpr float turnFactor = 0.00625f;
        static constexpr float separationDist = 15.0f;
        static constexpr float separationFactor = 1.5f;

        static void InitializeBoids(int len, Cord* boidsN) {
            boidTotal = len;
            boids = boidsN;
            for (int i = 0; i < len; i++) {
                boids[i] = boidsN[i];
            }
        }

        static void EvaluateBoids() {
            if (boidTotal == 0) { std::cout << "You need to call InitializeBoids() before using any boid funcitons" << std::endl; return; }
            //InitializeRule1();
            //InitializeRule3();
            for (int i = 0; i < boidTotal; i++) {
                boids[i].velo += GetRule1and3(i) + GetRule2(i) + GetRule4(i);
                if (boids[i].velo.SqMagnitude() > maxVelo*maxVelo) { boids[i].velo = boids[i].velo.Normalized() * maxVelo; }
            }
            for (int i = 0; i < boidTotal; i++) {
                boids[i].Move();
            }
            //std::cout << boids[0].pos << " " << boids[0].velo << std::endl;
        }

        static void DrawBoids() {
            if (boidTotal == 0) { std::cout << "You need to call InitializeBoids() before using any boid funcitons" << std::endl; return; }
            for (int i = 0; i < boidTotal; i++) {
                boids[i].Draw();
            }
        }
        
        // Initialize the Cohesion
        static void InitializeRule1() { 
            rule1 = zerozero;
            for (int i = 0; i < boidTotal; i++) {
                rule1 += boids[i].pos;
            }
        }
        // Get the Cohesion for boid[id]
        static Vector2 GetRule1(int id) { 
            return (rule1 - boids[id].pos)/(boidTotal-1) * cohesionFactor;
            //rule1 += (Helpful::SqDistance(snakes[i].pos, snakes[j].pos) < sight*sight) ? snakes[j].pos : zerozero;
        }

        // Get the Separation for boid[id]
        static Vector2 GetRule2(int id) {
            rule2 = zerozero;
            for (int i = 0; i < boidTotal; i++) {
                if (id == i) {continue;}

                rule2 -= (Helpful::SqDistance(boids[id].pos, boids[i].pos) < separationDist*separationDist) ? (boids[i].pos - boids[id].pos) : zerozero;
            }
            return rule2 * separationFactor;
        }

        static Vector2 GetRule1and3(int id) {
            rule1 = zerozero;
            rule3 = zerozero;
            int total = 0;
            for (int i = 0; i < boidTotal; i++) {
                if (id == i) {continue;}
                if (Helpful::SqDistance(boids[id].pos, boids[i].pos) < sight*sight) {
                    rule1 += boids[i].pos;
                    rule3 += boids[i].velo;
                    total++;
                }
            }
            return (total > 0) ? (rule1 / total) * cohesionFactor + (rule3 / total) * alignmentFactor : zerozero;
        }

        // Initialize the Alignment
        static void InitializeRule3() { 
            rule1 = zerozero;
            for (int i = 0; i < boidTotal; i++) {
                rule3 += boids[i].velo;
            }
        }
        // Get the Alignment for boid[id]
        static Vector2 GetRule3(int id) { 
            return (rule3 - boids[id].velo)/(boidTotal-1) * alignmentFactor;
        }

        // Bound the boids smoothly
        static Vector2 GetRule4(int id) {
            rule4 = zerozero;
            // Handle X-Bounds
            if (boids[id].pos.x > (WIDTH - boundDist)) { 
                rule4.x -= (boids[id].pos.x - (WIDTH - boundDist)); 
            } else if (boids[id].pos.x < boundDist) { 
                rule4.x += (boundDist - boids[id].pos.x); 
            }
            // Handle Y-Bounds
            if (boids[id].pos.y > (HEIGHT - boundDist)) { 
                rule4.y -= (boids[id].pos.y - (HEIGHT - boundDist)); 
            } else if (boids[id].pos.y < boundDist) { 
                rule4.y += (boundDist - boids[id].pos.y); 
            }
            return rule4 * turnFactor;
        }
};