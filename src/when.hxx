// lascra "when" keyword

/* Usage:
 * (when (event)
 *	do something...
 * )
*/

/* Events:
*  - flag
*  - click
*  - (pressed space)
*  - (loudness 90)
*  - (received "My Broadcast")
*  - (backdrop "My Backdrop")
*  - clone
*/
/* Extension Events:
 * Video Sensing:
 * (video_motion 80)
 * Makey Makey:
 * (makey_pressed space)
 * (makey_sequence "left up right")
 * Micro Bit:
 * (micro_pressed A)
 * (micro_tilted any)
 * (micro_event moved)
 * (micro_pin 0)
 * LEGO EV3:
 * (ev3_button 1)
 * (ev3_distance 5)
 * (ev3_brightness 50)
 * LEGO Boost:
 * (boost_color "any color")
 * (boost_tilted any)
 * WeDo 2.0 Sensors:
 * (wedo_distance < 50)
 * (wedo_tilted any)
 * Force and Acceleration:
 * (forceaccel_event shaken)
 * (forceaccel_sensor pushed)
 * (forceaccel_tilted any)
*/

#include <bparser/node.hxx>

void when(bparser::node& sprite, bparser::node& code);
