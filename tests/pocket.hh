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
      && test_box_pocket_4robots()
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

};

} //tests
} //robots_core
