import type { Card } from "@components/BankCard/consts";

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

  async endSession(): Promise<void> {}
}

export default AtmAPI;
