#include <iostream>
#include <vector>
#include <algorithm>


#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main ( int argc, char** argv )
{
    // the pose of robots
    Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);

    // normalize(): divides it by its own norm.
    q1.normalize();
    q2.normalize();
    Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
    Vector3d p1(0.5, 0, 0.2);

    Isometry3d T1w(q1), T2w(q2);
    T1w.pretranslate (t1); 
    T2w.pretranslate (t2);
    //cout << "T1w: " << T1w << end;
    //cout << "T2w: " << T2w << end;

    Vector3d p2 = T2w * T1w.inverse() * p1;
    cout << "T2w" << endl << T2w.matrix() << endl;
    cout << "T1w_inverse" << endl << T1w.inverse().matrix() << endl;
    cout << "p1" << endl << p1.transpose() << endl;
    cout << "p2" << endl << p2.transpose() << endl;

    return 0;
}