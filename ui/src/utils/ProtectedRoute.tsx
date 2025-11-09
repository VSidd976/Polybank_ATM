import type { PropsWithChildren, ReactNode } from "react";
import { useCard } from "./stores/cardStore";
import { Navigate } from "react-router-dom";

const ProtectedRoute = ({ children }: PropsWithChildren): ReactNode => {
  const { card } = useCard();
  console.log({ card });
  if (!card) return <Navigate to={"/?logout=true"} />;
  return children;
};

export default ProtectedRoute;
