export function fmod(a, b) {
  if (b === 0) {
    throw new Error("Division by zero is not allowed.");
  }
  let r = 0;
  while (r < a) {
    r += Math.abs(b);
  }
  return a - (r - Math.abs(b));
}
