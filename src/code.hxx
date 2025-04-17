// lascra code system
// Used in body of "when" and "subroutine"

/* Examples:
*  - (wait 1)
*  - (move 10)
*  - (say "Hi!")	// say
*  - (say "long" 10)	// say .. for ..
*  - (append "thing" "My List")
*  - (delete 1 "My List")
*  - (delete_all "My List")
*  - (insert "thing" 1 "My List")
*  - (replace 1 "My List" "thing")
*  - (delete_clone)
*  - (repeat 10 ...)
*  - (forever ...)
*  - (if (condition) (then ...) (else ...))
*  - (wait (condition))
*  - (stop all)
*  - (set_sound_effect pitch 100)
*  - (clear_sound_effects)
*  - (stop_all_sounds)
*  - (change_effect color 25)
*  - (set_effect color 0)
*  - (clear_effects)
*  - (show)
*  - (hide)
*  - (edge_bounce)
*/

#include <bparser/node.hxx>
#include <string>

// Returns block id
std::string substack(bparser::node& sprite, bparser::node& param, int offset, std::string parentid);
std::string code(bparser::node& sprite, bparser::node& code, bparser::node* previf = nullptr);
