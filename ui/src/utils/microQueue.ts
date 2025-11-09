export const microQueue = (callBack: () => void): void => {
  setTimeout(callBack, 0);
};
