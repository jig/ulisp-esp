
// Look at http://www.ulisp.com/show?2E0A for how uLisp functions are to be implemented

volatile long int rounds = 0;

// (rounds)
object *fn_rounds (object *args, object *env) {
  (void) env;
  int r = rounds;
  rounds = 0;
  return number(r);
}

// (reset)
object *fn_reset (object *args, object *env) {
  (void) env;
  asm volatile ("  jmp 0");
  return nil;
}

// (battery)
object *fn_battery (object *args, object *env) {
  (void) env;
  int pin = checkinteger(BATTERY, first(args));
  checkanalogread(pin);
  return number(analogRead(pin));
}

// (speed ...) has two modes: all motors or a single motor
// (speed 0...255) sets all motors to 0...255
// (speed '(0 255)) sets motor 0 to 255 
// (speed -255) sets all motors to -255
object *fn_speed (object *args, object *env) {
  (void) args, (void) env;
  object *arg1 = first(args);
  if integerp(arg1) {
      object *speed = arg1;
      // ...
      return nil
  } else {
    if (arg1 == NULL || cdr(arg1) == NULL) {
        error(PSTR("argument is not a list of two items"));
    }
    int motorID = integer(first(arg1));
    int motorValue = integer(second(arg1));
  }
  return nil;
}

// (servo '(#servo #value))
// (servo '(0 255))
// (servo '(0 0))
object *fn_servo (object *args, object *env) {
  (void) args, (void) env;
  object *arg1 = first(args);
  if (arg1 == NULL || cdr(arg1) == NULL) {
      error(PSTR("argument is not a list of two items"));
  }
  int servoID = integer(first(arg1));
  int servoValue = integer(second(arg1));
  return nil;
}

// Borinot implementation

void borinotloop() {
  ++rounds;
}
