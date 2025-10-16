import { useMemo } from "react";

export const useMemoValue = <Args extends unknown[], Return>(
  callback: (...args: Args) => Return,
  args: Args,
): Return => {
  return useMemo(() => callback(...args), args);
};
