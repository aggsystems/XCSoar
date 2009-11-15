/* Generated by Together */

#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H

struct AIRCRAFT_STATE;
struct GEOPOINT;
struct GeoVector;

class TaskStats;
class TaskPoint;

#include "Util/GenericVisitor.hpp"

class TaskInterface:
  public BaseVisitable<> 
{
public:

/** 
 * Set index in sequence of active task point.  Concrete classes providing
 * this method should ensure the index is valid.
 * 
 * @param new_index Desired sequence index of active task point
 */
  virtual void setActiveTaskPoint(unsigned new_index) = 0;

/** 
 * Accessor for active task point.  Typically could be used
 * to access information about the task point for user feedback.
 * 
 * @return Active task point
 */  
  virtual TaskPoint* getActiveTaskPoint() = 0;

/** 
 * Convenience function, calculates and returns a vector (distance and bearing)
 * to the active task point from the aircraft.
 * 
 * @param state Current aircraft state
 * 
 * @return Vector to target from aircraft
 */
  GeoVector get_active_vector(const AIRCRAFT_STATE &state);

/** 
 * Accessor for task statistics for this task
 * 
 * @return Task statistics reference
 */
  virtual const TaskStats& get_stats() const = 0;

/** 
 * Update internal states as flight progresses.  This may perform
 * callbacks to the task_events, and advance the active task point
 * based on task_behaviour.
 * 
 * @param state_now Aircraft state at this time step
 * @param state_last Aircraft state at previous time step
 * 
 * @return True if internal state changed
 */
  virtual bool update(const AIRCRAFT_STATE& state_now, 
                      const AIRCRAFT_STATE& state_last) = 0;

/** 
 * Update internal states (non-essential) for housework, or where functions are slow
 * and would cause loss to real-time performance.
 * 
 * @param state_now Aircraft state at this time step
 * 
 * @return True if internal state changed
 */
  virtual bool update_idle(const AIRCRAFT_STATE &state_now) = 0;

#ifdef DO_PRINT
  virtual void print(const AIRCRAFT_STATE &state) = 0;
#endif

};
#endif //TASKINTERFACE_H
