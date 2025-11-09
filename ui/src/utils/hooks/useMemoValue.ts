import { useMemo, type DependencyList } from "react";

export const useMemoValue = <Args extends DependencyList, Return>(
  callback: (...args: Args) => Return,
  args: Args,
): Return => {
  return useMemo(() => callback(...args), args);
};
