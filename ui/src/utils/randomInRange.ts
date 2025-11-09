export function randomInRange(min: number, max: number) {
  return Math.ceil(Math.random() * (max - min) + min);
}
