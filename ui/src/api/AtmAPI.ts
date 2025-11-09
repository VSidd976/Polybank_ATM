import type { Card } from "@components/BankCard/consts";

export type AccountInfo = {
  balance: number;
};

class AtmAPI {
  constructor(private readonly card: Card) {}

  static of(card: Card): AtmAPI {
    return new AtmAPI(card);
  }
  async insertCard(): Promise<boolean> {
    // impl
    console.log("Inserting a card", this.card);
    return true;
  }

  async inputPIN(pin: string): Promise<boolean> {
    console.log("Sending a pin", pin);
    return true;
  }

  async cashOut(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return true;
  }

  async putMoney(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return true;
  }

  async transferMoney(amount: number, to: string): Promise<boolean> {
    console.log({ amount, to });
    return true;
  }

  async getInfo(): Promise<AccountInfo> {
    return {
      balance: 200,
    };
  }

  async endSession(): Promise<void> {}
}

export default AtmAPI;
