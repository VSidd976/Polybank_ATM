import type { FC } from "react";

export const withProps = <T extends object, P extends Partial<T>>(
  Component: FC<T>,
  defaultProps: Partial<P>,
): FC<Omit<T, keyof P>> => {
  const InnerComponent = (props: T) => (
    <Component {...(props as T)} {...defaultProps} />
  );
  return InnerComponent as FC<Omit<T, keyof P>>;
};
