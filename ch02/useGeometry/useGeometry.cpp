#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

/****************************
* 本程序演示了 Eigen 几何模块的使用方法
****************************/

int main ( int argc, char** argv )
{
    // Eigen/Geometry module provides a variety of rotation and translation representations
    // 3D rotation matrix directly using Matrix3d or Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // The rotation vector uses AngleAxis, the underlying layer is not directly Matrix,
    // but the operation can be treated as a matrix (because the operator is overloaded)
    Eigen::AngleAxisd rotation_vector ( M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     // Rotate 45 degrees along the Z axis
    cout .precision(3);
    cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;                // Convert to matrix with matrix()
    // can also be assigned directly
    rotation_matrix = rotation_vector.toRotationMatrix();
    // coordinate transformation with AngleAxis
    Eigen::Vector3d v ( 1,0,0 );
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // Or use a rotation matrix
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    // Euler angle: You can convert the rotation matrix directly into Euler angles
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYX order, ie roll pitch yaw order
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

    // Euclidean transformation matrix using Eigen::Isometry
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // Although called 3d, it is essentially a 4*4 matrix
    T.rotate ( rotation_vector );                                     // Rotate according to rotation_vector
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // Set the translation vector to (1,3,4)
    cout << "Transform matrix = \n" << T.matrix() <<endl;

    // Use the transformation matrix for coordinate transformation
    Eigen::Vector3d v_transformed = T*v;                              // Equivalent to R*v+t
    cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

    // For affine and projective transformations,
    // use Eigen::Affine3d and Eigen::Projective3d.

    // Quaternion
    // You can assign AngleAxis directly to quaternions, and vice versa
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;   // Note that the order of coeffs is
    // (x, y, z, w), w is the real part, the first three are the imaginary part
    // can also assign a rotation matrix to it
    q = Eigen::Quaterniond ( rotation_matrix );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;
    // Rotate a vector with a quaternion and use overloaded multiplication
    v_rotated = q*v; // 注意数学上是qvq^{-1}
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // expressed by regular vector multiplication, it should be calculated as follows
    cout << "should be equal to " << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

    return 0;
}