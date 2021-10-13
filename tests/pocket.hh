#include <robots_core/board.hh>
#include <robots_core/pocket/pocket.hh>

#include <iostream>
#include <cassert>
#include <algorithm>

namespace robots_core {
namespace tests {

using namespace robots_core::pocket;

struct PocketTests {

  static void run(){
    bool const passed = test_box_pocket_4robots()
      && test_box_pocket_1adjrobot_3OOB()
      && test_box_pocket_1robot_3OOB()
      && test_nonbox_pocket_2robot_2OOB()
      ;

    if( passed ) std::cout << "PASSED PocketTests" << std::endl;
    else         std::cout << "FAILED PocketTests" << std::endl;
  }

  static bool test_box_pocket_4robots(){
    Board const b("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000101002010000000010000000000030000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000100000000000000000000000000100010000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    Pocket const p = create_pocket( b );
    
    assert( p.center == b.human_position() );

    using Card = CardinalPost;

    { //UP Post
      Post const & post = p.cardinal_posts[Card::UP|0];
      assert( post.pos == p.center + Position({0, 1}) );
      assert( post.distance == 1 );
    }

    { //DOWN Post
      Post const & post = p.cardinal_posts[Card::DOWN|0];
      assert( post.pos == p.center - Position({0, 2}) );
      assert( post.distance == 2 );
    }

    { //RIGHT Post
      Post const & post = p.cardinal_posts[Card::RIGHT|0];
      assert( post.pos == p.center + Position({1, 0}) );
      assert( post.distance == 1 );
    }

    { //LEFT Post
      Post const & post = p.cardinal_posts[Card::LEFT|0];
      assert( post.pos == p.center - Position({8, 0}) );
      assert( post.distance == 8 );
    }

    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] == 9 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] == 2 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] == 10 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] == 3 );

    return true;
  }

  static bool test_box_pocket_1adjrobot_3OOB(){
    Board const b("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000010000000000000000000000011001000000001000000000000030000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000010000000000000000000000000000101000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000100000000000000000010000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    Pocket const p = create_pocket( b );
    
    assert( p.center == b.human_position() );

    using Card = CardinalPost;

    { //UP Post
      Post const & post = p.cardinal_posts[Card::UP|0];
      assert( post.pos == p.center + Position({0, 22}) );
      assert( post.distance == 22 );
    }

    { //DOWN Post
      Post const & post = p.cardinal_posts[Card::DOWN|0];
      assert( post.pos == p.center - Position({0, 7}) );
      assert( post.distance == 7 );
    }

    { //RIGHT Post
      Post const & post = p.cardinal_posts[Card::RIGHT|0];
      assert( post.pos == p.center + Position({7, 0}) );
      assert( post.distance == 7 );
    }

    { //LEFT Post
      Post const & post = p.cardinal_posts[Card::LEFT|0];
      assert( post.pos == p.center );
      assert( post.distance == 0 );
    }

    std::cout << "Diagonal Offsets: " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] << std::endl;

    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] == 22 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] == 29 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] == 7 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] == 14 );

    return true;
  }

  static bool test_box_pocket_1robot_3OOB(){
    Board const b("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000030003000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000030000000000000000000000000000000000000000000000000000000000000000000010000000000000000300000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000003000000000000000000000000000000003003001000200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    Pocket const p = create_pocket( b );
    
    assert( p.center == b.human_position() );

    using Card = CardinalPost;

    { //UP Post
      Post const & post = p.cardinal_posts[Card::UP|0];
      assert( post.pos == p.center + Position({0, 2}) );
      assert( post.distance == 2 );
    }

    { //DOWN Post
      Post const & post = p.cardinal_posts[Card::DOWN|0];
      assert( post.pos == p.center - Position({0, 3}) );
      assert( post.distance == 3 );
    }

    { //RIGHT Post
      Post const & post = p.cardinal_posts[Card::RIGHT|0];
      assert( post.pos == p.center + Position({5, 0}) );
      assert( post.distance == 5 );
    }

    { //LEFT Post
      Post const & post = p.cardinal_posts[Card::LEFT|0];
      assert( post.pos == p.center - Position({39, 0}) );
      assert( post.distance == 39 );
    }

    std::cout << "Diagonal Offsets: " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] << std::endl;

    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] == 41 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] == 7 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] == 42 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] == 8 );

    return true;
  }

  static bool test_nonbox_pocket_2robot_2OOB(){
    Board const b("000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000100000000000000000100000000000000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000001000001000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000010100000000000000100000000000000000000000000000000000000000010000000000000001001000001000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000001000000000000000001000000200000000000000000000000000001001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000100000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000010000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    Pocket const p = create_pocket( b );
    
    assert( p.center == b.human_position() );

    using Card = CardinalPost;

    { //UP Post
      Post const & post = p.cardinal_posts[Card::UP|0];
      assert( post.distance == 14 );
    }

    { //DOWN Post
      Post const & post = p.cardinal_posts[Card::DOWN|0];
      assert( post.distance == 6 );
    }

    { //RIGHT Post
      Post const & post = p.cardinal_posts[Card::RIGHT|0];
      assert( post.distance == 21 );
    }

    { //LEFT Post
      Post const & post = p.cardinal_posts[Card::LEFT|0];
      assert( post.distance == 19 );
    }

    std::cout << "Diagonal Offsets: " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] << " " << (int)p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] << std::endl;

    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_LEFT|0 ] == 5 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::UP_RIGHT|0 ] == 2 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_LEFT|0 ] == 17 );
    assert( p.diagonal_offsets[ DiagonalQuadrant::DOWN_RIGHT|0 ] == 1 );

    return true;
  }


};

} //tests
} //robots_core
