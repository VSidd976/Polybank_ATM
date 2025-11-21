import { useMemo } from "react";

export const useMemoValue = <Args extends readonly unknown[], Return>(
  callback: (...args: Args) => Return,
  args: [...Args],
): Return => {
  return useMemo(() => callback(...args), args);
};
